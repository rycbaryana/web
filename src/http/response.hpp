#pragma once
#include <fstream>
#include <string>
#include <unordered_map>
#include "config.hpp"

class HttpResponse {
    static constexpr auto HTTP_VER = config::HTTP_VER;
    static constexpr auto DELIM = config::DELIM;

public:
    HttpResponse() = default;
    HttpResponse(int status_code, std::string reason)
        : status_code(status_code), reason(std::move(reason)) {
    }
    std::string ToString() {
        std::string response =
            HTTP_VER + ' ' + std::to_string(status_code) + ' ' + reason + DELIM;
        for (auto &[name, value] : headers_) {
            response += name + ": " + value + DELIM;
        }
        response += DELIM;
        response += body_;
        return response;
    }
    void AddHeader(const std::string &name, const std::string &value) {
        headers_[name] = value;
    }
    void AddBody(const std::string &content) {
        body_ += content;
    }
    void SetLength(size_t length) {
        AddHeader("Content-Length", std::to_string(length));
    }
    static HttpResponse Created() {
        return HttpResponse{201, "Created"};
    }
    static HttpResponse Ok() {
        return HttpResponse{200, "OK"};
    }
    static HttpResponse NotFound() {
        return HttpResponse{404, "Not Found"};
    }
    static HttpResponse PlainText(const std::string &content) {
        auto response = HttpResponse::Ok();
        response.AddHeader("Content-Type", "text/plain");
        response.SetLength(content.size());
        response.AddBody(content);
        return response;
    }
    int status_code{};
    std::string reason;
private:
    std::unordered_map<std::string, std::string> headers_;
    std::string body_;
};