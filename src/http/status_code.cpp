#include <http/status_code.hpp>

namespace http {
    std::string StatusCodeString(StatusCode status) {
        switch(status) {
            case StatusCode::OK:
            return "OK";
            case StatusCode::Created:
            return "Created";
            case StatusCode::Accepted:
            return "Accepted";
            case StatusCode::MovedPermanently:
            return "Moved Permanently";
            case StatusCode::BadRequest:
            return "Bad Request";
            case StatusCode::Unauthorized:
            return "Unathorized";
            case StatusCode::Forbidden:
            return "Forbidden";
            case StatusCode::NotFound:
            return "Not Found";
            case StatusCode::MethodNotAllow:
            return "Method Not Allowed";
            case StatusCode::InternalServerError:
            return "Internal Server Error";
            default:
            return "Unknown status code";
        }
    }
    std::string ToString(StatusCode status) {
        return std::to_string(static_cast<std::underlying_type_t<StatusCode>>(status)) + ' ' + StatusCodeString(status);
    }
}