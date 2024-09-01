#include <iostream>
#include <http/client/client.hpp>
int main() {
    http::Request req(http::Url("http://www.google.com/"), http::HttpMethod::GET);
    auto resp = http::client::send(req);
    return 0;
}