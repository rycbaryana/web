#pragma once
#include <stdexcept>
#include <string>

#include "../io/utils.hpp"
#include "config.hpp"
#include <unordered_map>
#include <ranges>
#include "url.hpp"

enum class HttpMethod {
    GET,
    POST,
    PUT,
    DELETE,
};

inline HttpMethod fromString(const std::string method) {
    switch (method[0]) {
        case 'G':
            return HttpMethod::GET;
        case 'P':
            return method[1] == 'O' ? HttpMethod::POST : HttpMethod::PUT;
        case 'D':
            return HttpMethod::DELETE;
        default:
            throw std::runtime_error("Unsupported HTTP method");
    }
}

inline std::string toString(HttpMethod method) {
    std::string methods[] {"GET", "POST", "PUT", "DELETE"};
    return methods[static_cast<int>(method)];
}

class HttpRequest {
    static constexpr auto HTTP_VER = config::HTTP_VER;
    static constexpr auto DELIM = config::DELIM;

public:
    HttpRequest(const std::string_view& request) {
        auto tokens = Split(request, DELIM);
        if (!tokens.back().empty()) {
            body_ = tokens.back();
            tokens.pop_back();
        }
        while (tokens.back().empty()) {
            tokens.pop_back();
        }
        auto status = Split(tokens[0], " ");
        method_ = fromString(status[0]);
        url_ = Url(status[1]);
        protocol_ = status[2];
        for (auto token : tokens | std::ranges::views::drop(1)) {
            auto header = Split(token, ": ");
            headers_.emplace(header[0], header[1]);
        }
    }
    std::string GetHeader(const std::string& header) const {
        if (auto it = headers_.find(header); it != headers_.end()) {
            return it->second;
        }
        return std::string();
    }
    std::string Protocol() {
        return protocol_;
    }
    HttpMethod Method() {
        return method_;
    }
    Url URL() {
        return url_;
    }
    std::string Body() {
        return body_;
    }

private:
    HttpMethod method_;
    Url url_;
    std::unordered_map<std::string, std::string> headers_;
    std::string protocol_;
    std::string body_;

};