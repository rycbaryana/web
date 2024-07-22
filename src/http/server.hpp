#pragma once
#include "../server.hpp"
#include "../thread_pool/thread_pool.hpp"
#include "router/router.hpp"

class HttpServer : public Server {
public:
    HttpServer(int port, size_t workers) : Server(port), pool_(workers) {
    }
    void Run() {
        Listen();
        for (int i = 0; i < pool_.Size(); ++i) {
            pool_.Submit([this]() {
                while (true) {
                    auto [reader, writer] = Accept();
                    auto request = HttpRequest(reader.Read());
                    HttpResponse response = router.Serve(request);
                    writer.Write(response.ToString());
                }
            });
        }
    }
    HttpRouter router;

private:
    ThreadPool pool_;
};
