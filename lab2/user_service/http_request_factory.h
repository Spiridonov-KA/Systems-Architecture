#pragma once

#include <iostream>

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerRequest.h"

#include "user_handler.h"

class HTTPRequestFactory : public Poco::Net::HTTPRequestHandlerFactory {
public:
    HTTPRequestFactory(const std::string& format) : format_(format) {}

    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request) {
        std::cout << "request:" << request.getMethod() << ' ' << request.getURI() << std::endl;
        if (request.getURI().starts_with("/user")) {
            return new UserHandler(format_);
        }
        return 0;
    }

private:
    std::string format_;
};
