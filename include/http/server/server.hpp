#pragma once
#include "router/router.hpp"
#include <net/base_server.hpp>
#include <thread_pool/thread_pool.hpp>

namespace http {
class HttpServer : public net::BaseServer {
public:
    HttpServer(int port, size_t workers) : BaseServer(port), pool_(workers) {
    }

    HttpRouter& Router() & {
        return router_;
    }

    void Run();

private:
    HttpRouter router_;
    threads::ThreadPool pool_;
};

}  // namespace http
