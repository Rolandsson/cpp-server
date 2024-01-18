#pragma once

#include "http.hpp"

class InboxServlet : public HttpServlet {
    
    public:
        void doGet(HttpRequest request) override;
        void doPost(HttpRequest request) override;
};