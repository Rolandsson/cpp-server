#include <iostream>
#include "socket.hpp"
#include "servlet.hpp"
#include "http.hpp"

using std::endl;
using std::cerr;
using std::cout;

void serve(HttpRequest request);

int main(int argc, char const *argv[]) {
    ServerSocket socket {"0.0.0.0", 6060};

    while(true) {
        SOCKET client;  
        bool isSuccessful = socket.awaitClient(client);

        if(!isSuccessful) {
            cerr << "Attempted connection failed" << endl;
        }

        string data = socket.retrieveData(client);
        HttpRequest request {data};

        serve(request);

        socket.closeConnection(client);
    }
    
    return 0;
}

void serve(HttpRequest request) {
    HttpServlet *servlet;

    if(request.getPath() == "/inbox") {
        servlet = new InboxServlet();
    } else {
        servlet = new HttpServlet();
    }

    servlet->serve(request);
    delete servlet;
}

