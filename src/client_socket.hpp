#pragma once
#include "socket_utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <netinet/in.h>
#include <unistd.h>

class ClientSocket {
private:
    Socket client_socket;
    std::string client_ip;
    int client_port;
public:
    ClientSocket(Socket socket, const std::string &ip, int port);
    ~ClientSocket();
    void handle_http_request();
    std::string parse_http_request(const std::string &raw_request);
    std::string read_file_from_disk(const std::string &file_path);
    std::string generate_http_response(const std::string &content);
};