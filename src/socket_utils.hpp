#pragma once
#include <string>

class Socket {
private:
    int fd;
public:

    Socket(int fd);
    ~Socket();
    int get_fd() const;
    static Socket create_socket(int port);
    Socket accept_client(std::string &client_ip, int &client_port);
};