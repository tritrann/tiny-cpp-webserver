#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
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
    ssize_t send_data(const std::string &data);
    ssize_t receive_data(std::string &data);
    std::string parse_http_request(std::string &raw_request);
    std::string read_file_from_disk(const std::string &file_path);
};