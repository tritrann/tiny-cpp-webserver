#include <client_socket.hpp>

ClientSocket::ClientSocket(Socket socket, const std::string &ip, int port)
    : client_socket(socket), client_ip(ip), client_port(port) {}

ClientSocket::~ClientSocket() {
    close(client_socket.get_fd());
}

ClientSocket::handle_http_request() {
    std::string raw_request = client_socket.receive_raw_data();
    std::string request = client_socket.parse_http_request(raw_request);
    std::string file_path = request.substr(5, request.find(" HTTP/") - 5);
    std::string content = client_socket.read_file_from_disk(file_path);
    std::string response = client_socket.generate_http_response(content);
    client_socket.send_http_response(response);
}