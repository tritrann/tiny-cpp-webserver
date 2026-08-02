#include "socket_utils.hpp"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

Socket::Socket(int fd) : fd(fd) {}

Socket::~Socket() {
    if (fd >= 0) {
        close(fd);
    }
}

int Socket::get_fd() const {
    return fd;
}

Socket Socket::create_socket(int port) {
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cerr << "Failed to set socket options" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (sock_fd < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in address;
    std::memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(sock_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (listen(sock_fd, 5) < 0) {
        std::cerr << "Failed to listen on socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    return Socket(sock_fd);
}

Socket Socket::accept_client(std::string &client_ip, int &client_port) {
    struct sockaddr_in client_address;
    socklen_t client_len = sizeof(client_address);
    int client_fd = accept(this->fd, (struct sockaddr*)&client_address, &client_len);

    if (client_fd < 0) {
        std::cerr << "Failed to accept connection" << std::endl;
        return Socket(-1);
    }

    char ip_str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_address.sin_addr, ip_str, sizeof(ip_str));
    client_ip = std::string(ip_str);
    client_port = ntohs(client_address.sin_port);

    return Socket(client_fd);
}

std::string Socket::receive_raw_data() {
    char buffer[2048] = {0};
    ssize_t bytes_received = recv(this->fd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received <= 0) {
        std::cerr << "Failed to receive data" << std::endl;
        return "";
    }
    return std::string(buffer);
}

std::string Socket::send_http_response(const std::string &response) {
    ssize_t bytes_sent = send(this->fd, response.c_str(), response.size(), 0);
    if (bytes_sent < 0) {
        std::cerr << "Failed to send data" << std::endl;
        return "";
    }
    return std::to_string(bytes_sent);
}

