#include <winsock2.h>
#include <string>
#include <iostream>

using std::string;
using std::cerr;
using std::endl;

struct Settings {
    int port = 6060;
    string addr = "127.0.0.1";
} settings;

void exitEnv(int status, string msg) {
    cerr << msg << endl;
    WSACleanup();
    exit(status);
}

int main(int argc, char const *argv[]) {
    WSAData wsaData;

    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) {

    }

    return 0;
}
