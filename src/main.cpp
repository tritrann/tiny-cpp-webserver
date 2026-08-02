#include "web_server.hpp"
#include "client_socket.hpp"
#include "socket_utils.hpp"
#include <iostream>
#include <string>
#include <utility>


int main() {
    ServerSocket server(8080);
    std::cout << "Server is running on port 8080..." << std::endl;
    while (true) {
        std::string client_ip = "";
        int client_port = 0;
        Socket client_socket = server.accept_connection(client_ip, client_port);
        if (client_socket.get_fd() < 0) {
            std::cerr << "Failed to accept connection" << std::endl;
            continue;
        }
        std::cout << "Accepted connection from " << client_ip << ":" << client_port << std::endl;

    ClientSocket* client_handler = new ClientSocket(client_socket, client_ip, client_port);
    client_handler->handle_http_request();
    delete client_handler;
    }
}