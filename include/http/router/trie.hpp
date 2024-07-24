#pragma once
#include <string>
#include <memory>
#include <optional>
#include <http/handler.hpp>

// Trie for router with wildcard recognition
// Not thread safe
namespace impl {
using namespace http;
class RouterTrie {
    using Path = utils::Path;

public:
    enum class NodeType { ROOT, REGULAR, PARAM, CATCH_ALL };
    struct Node {
        std::string component;
        std::string wildcard_name;
        size_t wildcard_ind;
        std::optional<Handler> handler;
        NodeType type = NodeType::REGULAR;
        bool wildcard_child = false;
        std::unordered_map<std::string, std::shared_ptr<Node>> children;
        Node(const std::string& component = "", std::optional<Handler> handler = std::nullopt)
            : component(component), handler(std::move(handler)) {
        }
    };
    using NodePtr = std::shared_ptr<Node>;

public:
    RouterTrie() : base(std::make_shared<Node>("/")) {
        base->type = NodeType::ROOT;
    }
    void AddPath(const Path& path, Handler value);
    std::pair<std::optional<Handler>, Params> FindHandler(const Path& path) const;

private:
    std::optional<size_t> FindWildcard(const std::string& path);
    NodePtr InsertChild(NodePtr& node, const std::string& component, Params& params);
    NodePtr Go(const NodePtr& node, const std::string& component, Params& params) const;

private:
    NodePtr base;
};
}  // namespace impl
