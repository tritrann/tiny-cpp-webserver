#include <client_socket.hpp>

ClientSocket::ClientSocket(int fd, const std::string &ip, int port)
    : client_fd(fd), client_ip(ip), client_port(port) {}

ClientSocket::~ClientSocket() {
    if (client_fd >= 0) {
        close(client_fd);
    }
}

ClientSocket::receive_data(std::string &data) {
    char buffer[2048];
    ssize_t bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received < 0) {
        std::cerr << "Failed to receive data" << std::endl;
        return -1;
    }
    buffer[bytes_received] = '\0';
    data = std::string(buffer);
    return bytes_received;
}

ClientSocket::send_data(const std::string &data) {
    std::stringstream response_stream;
    response_stream << "HTTP/1.1 200 OK\r\n"
                    << "Content-Length: " << data.size() << "\r\n"
                    << "Content-Type: text/plain\r\n"
                    << "\r\n"
                    << data;

    std::string response = response_stream.str();
    ssize_t bytes_sent = send(client_fd, response.c_str(), response.size(), 0);
    if (bytes_sent < 0) {
        std::cerr << "Failed to send data" << std::endl;
        return -1;
    }
    return bytes_sent;
}

ClientSocket::parse_http_request(std::string &raw_request) {
    std::istringstream request_stream(raw_request);
    std::string method, path, version;
    request_stream >> method >> path >> version;
    std::cout << "Method: " << method << ", Path: " << path << ", Version: " << version << std::endl;
    if (path == "/") {
        return "public/index.html";
    } else if (path == "/about") {
        return "public/about.html";
    } else {
        return "404 Not Found";
    }
    return path;
}

ClientSocket::read_file_from_disk(const std::string &file_path) {
    std::ifstream file(file_path, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        return "<html><body><h1>404 Not Found</h1></body></html>";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}
