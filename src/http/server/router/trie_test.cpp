#include <catch2/catch_test_macros.hpp>
#include <http/server/router/trie.hpp>

using namespace http;

using impl::RouterTrie;
using utils::Path;

Request MOCK_REQUEST(Url("localhost:8080/hello"), HttpMethod::GET);


struct TestRequest {
    Path request;
    Path path;
    bool found;
    Params params;
};

auto MockHandler(const std::string& value) {
    return [=](Request, const Params&) {
        auto response = Response(StatusCode::OK);
        response.body(value);
        return response;
    };
}

void CheckRequests(RouterTrie& trie, std::vector<TestRequest> requests) {
    for (auto& [request, path, found, params] : requests) {
        auto [handler, p] = trie.FindHandler(request);
        REQUIRE(p == params);
        if (found) {
            REQUIRE(handler.has_value());
            REQUIRE((*handler)(MOCK_REQUEST, {}).GetBody() == path.Raw());
        } else {
            REQUIRE(!handler.has_value());
        }
    }
}

TEST_CASE("Simple", "[trie]") {
    RouterTrie trie;
    std::vector<Path> paths{Path("/a/b/c/"), Path("/b/a/"), Path("/"), Path("/a/b/")};
    for (auto& path : paths) {
        trie.AddPath(path, MockHandler(path.Raw()));
    }
    std::vector<TestRequest> requests{
        {Path("/a/b/c/"), Path("/a/b/c/"), true, {}},
        {Path("/b/a/"), Path("/b/a/"), true, {}},
        {Path("/"), Path("/"), true, {}},
        {Path(""), Path("/"), true, {}},
        {Path("/a/b/"), Path("/a/b/"), true, {}},
        {Path("/b/"), Path(""), false, {}},
        {Path("/a/"), Path(""), false, {}},
    };
    CheckRequests(trie, requests);
}
TEST_CASE("PARAM wildcard") {
    RouterTrie trie;
    std::vector<Path> paths{Path("/:name/"), Path("/:name/:surname/"),
                            Path("/:name/:surname/:birth"), Path("/")};
    for (auto& path : paths) {
        trie.AddPath(path, MockHandler(path.Raw()));
    }
    std::vector<TestRequest> requests{
        {Path("/Alex/"), Path("/:name/"), true, {{"name", "Alex"}}},
        {Path("/Alex/Smith/"),
         Path("/:name/:surname/"),
         true,
         {{"name", "Alex"}, {"surname", "Smith"}}},
        {Path("/a/b/2005"),
         Path("/:name/:surname/:birth"),
         true,
         {{"name", "a"}, {"surname", "b"}, {"birth", "2005"}}},
        {Path("/"), Path("/"), true, {}},
    };
    CheckRequests(trie, requests);
}
TEST_CASE("PARAM bad") {
    RouterTrie trie;
    std::vector<Path> good{Path("/a/"), Path("/b/:a/")};
    std::vector<Path> bad{Path("/:name/"), Path("/:a:b/"), Path("/:a/:a"), Path("/b/c/")};
    for (auto& path : good) {
        trie.AddPath(path, MockHandler(path.Raw()));
    }
    for (auto& path : bad) {
        REQUIRE_THROWS(trie.AddPath(path, MockHandler(path.Raw())));
    }
}
TEST_CASE("CATCH_ALL wildcard") {
    std::vector<Path> paths{Path("/*file/"), Path("/files/*file/")};
    std::vector<std::vector<TestRequest>> requests = {
        {
            {Path("/doc/index.html"), Path("/*file/"), true, {{"file", "/doc/index.html"}}},
            {Path("/a/"), Path("/*file/"), true, {{"file", "/a/"}}},
            {Path("/a"), Path("/*file/"), true, {{"file", "/a"}}},
            {Path("/"), Path("/*file/"), true, {{"file", "/"}}},
        },
        {
            {Path("/doc/index.html"), Path(""), false, {}},
            {Path("/files/index.html"), Path("/files/*file/"), true, {{"file", "/index.html"}}},
            {Path("/files/a/"), Path("/files/*file/"), true, {{"file", "/a/"}}},
            {Path("/files/"), Path("/files/*file/"), true, {{"file", "/"}}},
        }};
    for (size_t i = 0; i < paths.size(); ++i) {
        RouterTrie trie;
        trie.AddPath(paths[i], MockHandler(paths[i].Raw()));
        CheckRequests(trie, requests[i]);
    }
}