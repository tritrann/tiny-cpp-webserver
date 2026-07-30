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