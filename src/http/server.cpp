#include <http/server.hpp>
namespace http {

void HttpServer::Run() {
    Listen();
    for (int i = 0; i < pool_.Size(); ++i) {
        pool_.Submit([this]() {
            while (true) {
                // do
            }
        });
    }
}
}  // namespace http
