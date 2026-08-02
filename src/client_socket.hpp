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
    void handle_http_request();
};