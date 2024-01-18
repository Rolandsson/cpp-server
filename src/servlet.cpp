#include "servlet.hpp"
#include "http.hpp"
#include <iostream>

using std::endl;
using std::cout;


void InboxServlet::doGet(HttpRequest request) {
    cout << request.getBody() << endl;
}

void InboxServlet::doPost(HttpRequest request) {
    cout << request.getBody() << endl;
}

