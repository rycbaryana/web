#pragma once
#include <http/request.hpp>
#include <http/respone.hpp>
namespace http {
    namespace client {
        Response send(const Request& request);
    }
}