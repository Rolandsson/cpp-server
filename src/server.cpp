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

struct HttpHeader {
    string name;
    string value;
};

struct HttpRequest {
    string method;
    string version;
    string path;
    string body;
    vector<HttpHeader> headers;
};

void exitEnv(int status, string msg) {
    cerr << msg << endl;
    WSACleanup();
    exit(status);
}

SOCKET startup() {
    WSAData wsaData;
    SOCKET serverSocket;
    sockaddr_in sockAddr;

    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) {
        exitEnv(10, "Error starting the windows socket service");
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(serverSocket == INVALID_SOCKET) {
        exitEnv(11, "Error creating server socket");
    }

    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = inet_addr(settings.addr.c_str());
    sockAddr.sin_port = htons(settings.port);

    if(bind(serverSocket, (SOCKADDR*) &sockAddr, sizeof(sockAddr)) == SOCKET_ERROR) {
        exitEnv(12, "Error binding the server socket");
    }

    if(listen(serverSocket, 1)  == SOCKET_ERROR) {
        exitEnv(13, "Error listening with the server socket");
    }

    return serverSocket;
}

int main(int argc, char const *argv[]) {
    SOCKET clientSocket;
    SOCKET serverSocket = startup();
    
    while(true) {
        clientSocket = accept(serverSocket, NULL, NULL);

        string message;
        char recMessage[256];
        int size = -1;

        do {
            size = recv(clientSocket, recMessage, 256, 0);
            recMessage[size] = '\0';

            message.append(recMessage);
        } while(size == 256);


        std::cout << message << endl;

        closesocket(clientSocket);
    }

    return 0;
}

void serve(HttpRequest request) {
    if(request.getPath() == "/inbox") {
        if(request.getMethod() == "GET") {
            // hämta inbox
        } else if(request.getMethod() == "POST") {
            // skapa ett nytt meddelande i inbox:en
        }
    }
}