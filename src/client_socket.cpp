#include <client_socket.hpp>

ClientSocket::ClientSocket(int fd, const std::string &ip, int port)
    : client_fd(fd), client_ip(ip), client_port(port) {}