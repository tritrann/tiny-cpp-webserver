#include "client_socket.hpp"


ClientSocket::ClientSocket(Socket socket, const std::string &ip, int port)
    : client_socket(socket), client_ip(ip), client_port(port) {}

ClientSocket::~ClientSocket() {
    this->client_socket.close_socket();
    std::cout << "Closed connection with " << client_ip << ":" << client_port << std::endl;
}

std::string ClientSocket::parse_http_request(const std::string &raw_request) {
    if (raw_request.empty()) {
        return "public/404.html"; 
    }
    std::istringstream request_stream(raw_request);
    std::string method, path, version;
    request_stream >> method >> path >> version;

    if (method != "GET") {
        std::cerr << "Unsupported HTTP method: " << method << std::endl;
        return "public/404.html";
    }

    if (path == "/") {
        path = "public/index.html"; 
    }
    else if (path == "/about") {
        path = "public/about.html"; 
    }
    return path;
}

std::string ClientSocket::read_file_from_disk(const std::string &file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << file_path << std::endl;
        return "<html><body><h1>404 Not Found</h1></body></html>";
    }

    std::ostringstream content_stream;
    content_stream << file.rdbuf();
    file.close();
    return content_stream.str();
}

std::string ClientSocket::generate_http_response(const std::string &content) {
    std::ostringstream response_stream;
    response_stream << "HTTP/1.1 200 OK\r\n";
    response_stream << "Content-Length: " << content.size() << "\r\n";
    response_stream << "Content-Type: text/html; charset=UTF-8\r\n";
    response_stream << "\r\n";
    response_stream << content;
    return response_stream.str();
}

void ClientSocket::handle_http_request() {
    std::string raw_request = this->client_socket.receive_raw_data();
    if (raw_request.empty()) {
        std::cerr << "Failed to receive data from client" << std::endl;
        return;
    }
    std::string file_path = this->parse_http_request(raw_request);
    std::string content = this->read_file_from_disk(file_path);
    std::string response = this->generate_http_response(content);
    this->client_socket.send_http_response(response);
}
  