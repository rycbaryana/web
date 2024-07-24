#pragma once
#include <string>

namespace http {
enum class StatusCode {
    Invalid = 0,

    // 2xx success
    OK = 200,
    Created = 201,
    Accepted = 202,

    // 3xx redirect
    MovedPermanently = 301,

    // 4xx client error
    BadRequest = 400,
    Unauthorized = 401,
    Forbidden = 403,
    NotFound = 404,
    MethodNotAllow = 405,

    // 5xx server error
    InternalServerError = 500
};

std::string StatusCodeString(StatusCode status);

std::string ToString(StatusCode status);

}  // namespace http