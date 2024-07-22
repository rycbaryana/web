#pragma once
#include <stdexcept>
#include <unordered_map>
#include <string>
#include <memory>
#include <optional>
#include "../../path.hpp"
#include "../handler.hpp"

// Trie for router with wildcard recognition
// Not thread safe
class RouterTrie {
public:
    enum class NodeType { ROOT, REGULAR, PARAM, CATCH_ALL };

    struct Node {
        std::string component;
        std::string wildcard_name;
        size_t wildcard_ind;
        std::optional<HttpHandler> handler;
        NodeType type = NodeType::REGULAR;
        bool wildcard_child = false;
        std::unordered_map<std::string, std::shared_ptr<Node>> children;
        Node(const std::string& component = "", std::optional<HttpHandler> handler = std::nullopt)
            : component(component), handler(std::move(handler)) {
        }
    };
    using NodePtr = std::shared_ptr<Node>;

public:
    RouterTrie() : base(std::make_shared<Node>("/")) {
        base->type = NodeType::ROOT;
    }
    void AddPath(const Path& path, HttpHandler value) {
        auto cur = base;
        Params params;
        for (auto& component : path.Components()) {
            if (!component.empty()) {
                cur = InsertChild(cur, component, params);
            }
        }
        cur->handler = std::move(value);
    }
    std::pair<std::optional<HttpHandler>, Params> FindHandler(const Path& path) const {
        auto cur = base;
        std::unordered_map<std::string, std::string> params;
        for (auto& component : path.Components()) {
            cur = Go(cur, component, params);
            if (!cur) {
                break;
            }
        }
        if (!cur || !cur->handler) {
            return {std::nullopt, params};
        }
        return {HttpHandler([cur = std::move(cur)](HttpRequest request, Params params) {
                    return (*cur->handler)(request, params);
                }),
                std::move(params)};
    }

private:
    std::optional<size_t> FindWildcard(const std::string& path) {
        auto it =
            std::find_if(path.begin(), path.end(), [](char c) { return c == ':' || c == '*'; });
        if (it == path.end()) {
            return std::nullopt;
        }
        return it - path.begin();
    }
    NodePtr InsertChild(NodePtr& node, const std::string& component, Params& params) {
        if (!node) {
            return node;
        }
        if (node->type == NodeType::CATCH_ALL) {
            throw std::runtime_error("CATCH_ALL wildcard must be the last component in the path");
        }
        if (auto it = node->children.find(component); it != node->children.end()) {
            if (node->wildcard_child) {
                params[it->second->wildcard_name];
            }
            return it->second;
        }
        if (node->wildcard_child) {
            throw std::runtime_error("Path conflicts with existing wildcard");
        }
        auto child =
            node->children.emplace(component, std::make_shared<Node>(component)).first->second;
        if (component[0] == ':' || component[0] == '*') {
            if (component.size() == 1) {
                throw std::runtime_error("Wildcard must have a name");
            }
            if (node->children.size() > 1) {
                throw std::runtime_error("Wildcard conflicts with existing paths");
            }
            std::string wildcard = component.substr(1);
            if (FindWildcard(wildcard).has_value()) {
                throw std::runtime_error("Only one wildcard per component");
            }
            if (params.contains(wildcard)) {
                throw std::runtime_error("Wildcard redefinition");
            }
            child->type = component.starts_with(':') ? NodeType::PARAM : NodeType::CATCH_ALL;
            child->wildcard_name = wildcard;
            node->wildcard_child = true;
        }

        return child;
    }
    NodePtr Go(const NodePtr& node, const std::string& component,
               std::unordered_map<std::string, std::string>& params) const {
        if (node->wildcard_child || node->type == NodeType::CATCH_ALL) {
            auto wildcard_node =
                node->type == NodeType::CATCH_ALL ? node : node->children.begin()->second;
            if (wildcard_node->type == NodeType::PARAM) {
                if (component.empty()) {
                    return node;
                }
                if (params.contains(wildcard_node->component)) {
                    throw std::runtime_error("Wildcard redefinition");
                }
                params[wildcard_node->wildcard_name] = component;
            } else if (wildcard_node->type == NodeType::CATCH_ALL) {
                auto& value = params[wildcard_node->wildcard_name];
                value += '/';
                value += component;
            }
            return wildcard_node;
        } else if (component.empty()) {
            return node;
        } else {
            if (auto it = node->children.find(component); it != node->children.end()) {
                return it->second;
            } else {
                return NodePtr();
            }
        }
    }

private:
    NodePtr base;
};