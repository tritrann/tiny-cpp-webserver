
#include <netinet/in.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <string>


using namespace std;

class ServerSocket {
private:
    std::string protocol;
    std::string source_ip;
    int source_port;
    int server_fd;

public:
    ServerSocket(std::string protocol, std::string ip, int p);
    ~ServerSocket();
    int acceptConnection(std::string &client_ip, int &client_port);
};

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