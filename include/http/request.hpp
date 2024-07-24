#pragma once
#include "method.hpp"
#include "header.hpp"
#include <http/url.hpp>
#include <string>

namespace http {
class Request final {
public:
    Request() = default;

    Request(const Url& url, HttpMethod method = HttpMethod::UNSPECIFIED)
        : url_(url), method_(method) {
        header(Host, url.Host()).header(UserAgent, "rycbaryana's web").header(Accept, "*/*");
    }

    Request& method(HttpMethod method) {
        method_ = method;
        return *this;
    }
    Request& header(std::string_view header, std::vector<std::string> values) {
        headers_.emplace(header, std::move(values));
        return *this;
    }
    Request& header(std::string_view header, std::string_view value) {
        headers_.emplace(header, std::vector{std::string(value)});
        return *this;
    }
    Request& body(std::string_view body) {
        body_ = body;
        return *this;
    }

    const Url& GetUrl() const& {
        return url_;
    }

    const std::string& GetProto() const& {
        return proto_;
    }

    HttpMethod GetMethod() const {
        return method_;
    }

    const Headers& GetHeaders() const {
        return headers_;
    }

    const std::string& GetBody() const& {
        return body_;
    }

    std::string Dump() const;

private:
    std::string proto_{"HTTP/1.1"};  // HTTP/1.1
    Url url_;
    HttpMethod method_ { HttpMethod:: UNSPECIFIED };
    Headers headers_;
    std::string body_;
};
}  // namespace http
