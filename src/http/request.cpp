#include <http/request.hpp>

namespace http {
std::string Request::Dump() const {

    static constexpr std::string CRLF = "\r\n";
    static constexpr std::string KEY_VALUE_DELIM = ": ";

    std::string request = ToString(method_) + ' ' + "URL" + ' ' + proto_ + CRLF; 
    for (auto& [name, values] : headers_) {
        std::string_view delim;
        request += name + KEY_VALUE_DELIM;
        for (const auto& value : values) {
            request += delim;
            request += value;
            delim = ", ";
        }
        request += CRLF;
    }
    request += body_;
    return request;
}
}  // namespace http