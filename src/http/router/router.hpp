#pragma once
#include "trie.hpp"
#include <iostream>
class HttpRouter {
public:
    void GET(Path path, HttpHandler handler) {
        Handle(HttpMethod::GET, path, std::move(handler));
    }
    void POST(Path path, HttpHandler handler) {
        Handle(HttpMethod::POST, path, std::move(handler));
    }
    void PUT(Path path, HttpHandler handler) {
        Handle(HttpMethod::PUT, path, std::move(handler));
    }
    void DELETE(Path path, HttpHandler handler) {
        Handle(HttpMethod::DELETE, path, std::move(handler));
    }
    HttpResponse Serve(HttpRequest request) {
        auto [handler, params] =
            tries_[static_cast<int>(request.Method())].FindHandler(request.URL().path);
        if (handler.has_value()) {
            std::cout << toString(request.Method()) << ' ' << request.URL().path.Raw() << '\n';
            return (*handler)(request, params);
        } else {
            std::cout << request.URL().path.Raw() << " NOT FOUND \n";
            return HttpResponse::NotFound();
        }
    }

private:
    void Handle(HttpMethod method, Path path, HttpHandler handler) {
        tries_[static_cast<int>(method)].AddPath(path, std::move(handler));
    }

private:
    RouterTrie tries_[4];
};