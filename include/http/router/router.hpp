#pragma once
#include <http/handler.hpp>
#include <http/method.hpp>
#include <utils/path.hpp>
#include "trie.hpp"
namespace http {
class HttpRouter {
    using Path = utils::Path;
public:
    void GET(Path path, Handler handler) {
        Handle(HttpMethod::GET, path, std::move(handler));
    }
    void POST(Path path, Handler handler) {
        Handle(HttpMethod::POST, path, std::move(handler));
    }
    void PUT(Path path, Handler handler) {
        Handle(HttpMethod::PUT, path, std::move(handler));
    }
    void DELETE(Path path, Handler handler) {
        Handle(HttpMethod::DELETE, path, std::move(handler));
    }
    Response Serve(Request request);

private:
    void Handle(HttpMethod method, Path path, Handler handler);

private:
    impl::RouterTrie tries_[4];
};
}  // namespace http
