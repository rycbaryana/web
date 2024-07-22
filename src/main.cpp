#include "http/request.hpp"
#include "http/response.hpp"
#include "http/server.hpp"
#include <fstream>
#include <iostream>
#include <zlib.h>
#include <filesystem>
#include <iterator>

int main(int argc, char** argv) {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;
    HttpServer server(8080, 5);
    server.router.GET(Path("/"), [](HttpRequest, Params) { return HttpResponse::PlainText("Hello World!"); });
    server.router.GET(Path("/echo/:text"), [](HttpRequest request, Params p) {
        return HttpResponse::PlainText(p["text"]);
    });
    server.router.GET(Path("/favicon.ico"), [](HttpRequest request, Params p) {
        auto response = HttpResponse::Ok();
        response.AddHeader("Content-Type", "image/x-icon");
        std::ifstream img("favicon.ico", std::ifstream::binary);
        std::string content((std::istreambuf_iterator<char>(img)), std::istreambuf_iterator<char>());
        response.SetLength(content.size());
        response.AddBody(content);
        return response;
    });
    server.Run();
    return 0;
}
