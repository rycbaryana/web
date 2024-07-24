#pragma once
#include "status_code.hpp"
#include "header.hpp"
#include <string>
namespace http {
class Response final {
public:
    Response() = default;

    Response(StatusCode status) : status_(status) {};

    Response& header(std::string_view header, std::vector<std::string> values) {
        headers_.emplace(header, std::move(values));
        return *this;
    }
    Response& header(std::string_view header, std::string value) {
        headers_.emplace(header, std::vector{std::move(value)});
        return *this;
    }
    Response& body(std::string_view body) {
        body_ = body;
        return *this;
    }

    StatusCode GetStatus() const {
        return status_;
    } 

    const std::string& GetBody() const {
        return body_;
    }

    const Headers& GetHeaders() const {
        return headers_;
    }

    std::string Dump() const;

private:
    std::string proto_{"HTTP/1.1"};  // HTTP/1.1
    StatusCode status_;
    Headers headers_;
    std::string body_;
};
}  // namespace http
