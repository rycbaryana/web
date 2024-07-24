#include <http/router/router.hpp>
namespace http {

Response HttpRouter::Serve(Request request) {
    auto [handler, params] =
        tries_[static_cast<std::underlying_type_t<HttpMethod>>(request.GetMethod())].FindHandler(
            request.GetUrl().Path());
    if (handler.has_value()) {
        return (*handler)(request, params);
    } else {
        return Response(StatusCode::NotFound);
    }
}

void HttpRouter::Handle(HttpMethod method, Path path, Handler handler) {
    tries_[static_cast<int>(method)].AddPath(path, std::move(handler));
}

}  // namespace http