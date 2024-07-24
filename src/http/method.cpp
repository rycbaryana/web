#include <http/method.hpp>

namespace http {
std::string ToString(HttpMethod method) {
    switch (method) {
        case HttpMethod::GET:
            return "GET";
        case HttpMethod::POST:
            return "POST";
        case HttpMethod::PUT:
            return "PUT";
        case HttpMethod::DELETE:
            return "DELETE";
        default:
            return "UNKNOWN";
    }
}
}  // namespace http