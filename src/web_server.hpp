#include <iostream>
#include <string>
using namespace std;

class SOCKET {
private:
    std::string ip_address;
    int port;

public:
    SOCKET(std::string ip, int p) : ip_address(ip), port(p) {
        std::cout << "Socket created." << std::endl;
    }

    ~SOCKET() {
        std::cout << "Socket destroyed." << std::endl;
    }
};