#include "web_server.hpp"
#include <iostream>
#include <cstring>
#include <unistd.h>

ServerSocket::ServerSocket(std::string protocol, std::string ip, int p)
    : protocol(protocol), source_ip(ip), source_port(p) {
    // Create a socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Bind the socket to the specified IP and port
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(source_ip.c_str());
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