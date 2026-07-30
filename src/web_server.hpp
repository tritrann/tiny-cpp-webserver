
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <string>


using namespace std;

class ServerSocket {
private:
    Socket server_socket;

public:
    ServerSocket(int port);
    ~ServerSocket();
    int accept_connection(std::string &client_ip, int &client_port);
};

