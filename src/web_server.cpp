#include "web_server.hpp"

ServerSocket::ServerSocket(int port) 
    : server_socket(Socket::create_socket(port)) {
}

ServerSocket::~ServerSocket() {
    close(server_socket.get_fd());
}

Socket ServerSocket::accept_connection(std::string &client_ip, int &client_port) {
    return this->server_socket.accept_client(client_ip, client_port);
}
    