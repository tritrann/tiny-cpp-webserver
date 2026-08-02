#pragma once
#include <string>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
#include <sstream>

class Socket {
private:
    int fd;
public:
    Socket();
    Socket(int fd);
    ~Socket();
    int get_fd() const;
    static Socket create_socket(int port);
    Socket accept_client(std::string &client_ip, int &client_port);
    std::string receive_raw_data();
    std::string send_http_response(const std::string &response);
};