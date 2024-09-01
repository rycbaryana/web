#include <http/client/client.hpp>
#include <net/tcp.hpp>
namespace http {
namespace client {
Response send(const Request& request) {
    auto [reader, writer] =
        net::ConnectTCP(std::string(request.GetUrl().Host()), request.GetUrl().Port());
    writer.Write(request.Dump());
    auto resp = reader.Read();
    std::cout << resp << std::endl;
    return Response{StatusCode::OK};
}
}  // namespace client
}  // namespace http