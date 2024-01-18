#include "http.hpp"

#include <algorithm>
#include <iostream>

using std::find;
using std::cerr;
using std::endl;

HttpRequest::HttpRequest(string data) {
    string line;
    int startPos = 0;

    do {
        int eolIndex = data.find("\r\n", startPos);
        line = data.substr(startPos, eolIndex - startPos);

        if(line.find(":") != string::npos) {
            int deliIndex = line.find(":");
            string name = line.substr(0, deliIndex);
            string value = line.substr(deliIndex + 2, line.length() - deliIndex - 2);
            
            headers.push_back({ name, value });    
        } else if(line.find(" /") != string::npos) {
            method = line.substr(0, line.find(" "));
            path = line.substr(line.find("/"), line.find("HTTP") - 5);
            version = line.substr(line.find("HTTP") - 1, line.length() - (line.find("HTTP") - 1));
        }

        startPos = data.find("\n", eolIndex) + 1;

    } while(line != "" && startPos != string::npos);

    body = data.substr(startPos);
}

string HttpRequest::getMethod() { return method; }
string HttpRequest::getBody() { return body; }
string HttpRequest::getVersion() { return version; }
string HttpRequest::getPath() { return path; }
vector<HttpHeader> HttpRequest::getHeaders() { return headers; }

string HttpRequest::getHeader(string ref) {
    string value = "";
    int index = 0;

    while(value == "" && index < headers.size()) {
        if(headers.at(index).name == ref) {
            value = headers.at(index).value;
        } else {
            index++;
        }
    }

    if(index == headers.size()) {
        return "";
    } else {
        return value;
    }
}

void HttpServlet::handleUndefinedPath(HttpRequest request) {
    cerr 
        << "No handler found for requested path " << request.getPath() 
        << " - "
        << "[" << request.getMethod() << "]" << endl;
}

void HttpServlet::serve(HttpRequest request) {
    if(request.getMethod() == "GET") { 
        doGet(request); 
    } else if(request.getMethod() == "POST") { 
        doPost(request); 
    } else { 
        handleUndefinedPath(request); 
    }
}
