#pragma once
#include <iostream>
#include <string>
#include <netinet/in.h>

class ClientSocket {
private:
    int client_fd;
    std::string client_ip;
    int client_port;
public:
    ClientSocket(int fd, const std::string &ip, int port);
    ~ClientSocket();
    ssize_t sendData(const std::string &data);
    ssize_t receiveData(std::string &data);
    ssize_t parse_http_request(std::string &request, std::string &method, std::string &path, std::string &version);
};