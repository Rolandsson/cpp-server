#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

struct HttpHeader {
    string name;
    string value;
};

class HttpRequest {
    string version;
    string method;
    string body;
    string path;
    vector<HttpHeader> headers;

    public:
        HttpRequest(string data);
        string getVersion();
        string getMethod();
        string getBody();
        string getPath();
        vector<HttpHeader> getHeaders();
        string getHeader(string ref);
};

class HttpServlet {
    private:
        void handleUndefinedPath(HttpRequest request);

    public:
        void serve(HttpRequest request);
        virtual void doGet(HttpRequest request) { handleUndefinedPath(request); };
        virtual void doPost(HttpRequest request) { handleUndefinedPath(request); };
};