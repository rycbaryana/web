#include <http/respone.hpp>

namespace http {

std::string Response::Dump() const {

    static constexpr std::string CRLF = "\r\n";
    static constexpr std::string KEY_VALUE_DELIM = ": ";

    std::string response = proto_ + ' ' + ToString(status_) + CRLF;
    for (auto& [name, values] : headers_) {
        std::string_view delim;
        response += name + KEY_VALUE_DELIM;
        for (const auto& value : values) {
            response += delim;
            response += value;
            delim = ", ";
        }
        response += CRLF;
    }
    response += body_;
    return response;
}
}  // namespace http