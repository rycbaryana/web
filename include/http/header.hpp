#pragma once

#include <unordered_map>
#include <string>
#include <vector>
#include <utils/str_hash.hpp>

namespace http {

using Headers = std::unordered_map<std::string, std::vector<std::string>, utils::StringHash>; // transparent

class Header {
public:
    explicit constexpr Header(std::string_view name) : name_(name) {
    }
    operator std::string() const {
        return std::string(name_);
    }
    operator std::string_view() const {
        return name_;
    }

private:
    const std::string_view name_;
};

inline constexpr Header ContentType {"Content-Type"};
inline constexpr Header ContentLength {"Content-Length"};
inline constexpr Header ContentEncoding {"Content-Encoding"};
inline constexpr Header CacheControl {"Cache-Control"};
inline constexpr Header Expires {"Expires"};
inline constexpr Header LastModified {"Last-Modified"};
inline constexpr Header ETag {"ETag"};
inline constexpr Header Location {"Location"};
inline constexpr Header SetCookie {"Set-Cookie"};
inline constexpr Header Authorization {"Authorization"};
inline constexpr Header WWWAuthenticate {"WWW-Authenticate"};
inline constexpr Header AccessControlAllowOrigin {"Access-Control-Allow-Origin"};
inline constexpr Header AccessControlAllowMethods {"Access-Control-Allow-Methods"};
inline constexpr Header AccessControlAllowHeaders {"Access-Control-Allow-Headers"};
inline constexpr Header AccessControlExposeHeaders {"Access-Control-Expose-Headers"};
inline constexpr Header AccessControlMaxAge {"Access-Control-Max-Age"};
inline constexpr Header XForwardedFor {"X-Forwarded-For"};
inline constexpr Header XRealIP {"X-Real-IP"};
inline constexpr Header Referer {"Referer"};
inline constexpr Header UserAgent {"User-Agent"};
inline constexpr Header Accept {"Accept"};
inline constexpr Header AcceptLanguage {"Accept-Language"};
inline constexpr Header AcceptEncoding {"Accept-Encoding"};
inline constexpr Header Host {"Host"};

}  // namespace http