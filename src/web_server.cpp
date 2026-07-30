#include "web_server.hpp"
#include <iostream>
#include <cstring>
#include <unistd.h>

ServerSocket::ServerSocket(std::string protocol, std::string ip, int p)
    : protocol(protocol), source_ip(ip), source_port(p) {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    inet_pton(AF_INET, source_ip.c_str(), &address.sin_addr);
    address.sin_port = htons(source_port);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    if (listen(server_fd, 5) < 0) {
        std::cerr << "Failed to listen on socket" << std::endl;
        exit(EXIT_FAILURE);
    }
}

ServerSocket::~ServerSocket() {
    close(server_fd);
}

ServerSocket::acceptConnection(std::string &client_ip, int &client_port) {
    sockaddr_in client_address;
    socklen_t client_len = sizeof(client_address);
    int client_fd = accept(server_fd, (struct sockaddr*)&client_address, &client_len);

    if (client_fd < 0) {
        std::cerr << "Failed to accept connection" << std::endl;
        return -1;
    }

    char ip_str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_address.sin_addr, ip_str, sizeof(ip_str));
    client_ip = std::string(ip_str);
    client_port = ntohs(client_address.sin_port);

    return client_fd;
}