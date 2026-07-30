
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

