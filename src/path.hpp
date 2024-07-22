#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include "io/utils.hpp"

struct Path {
public:
    Path() = default;
    Path(std::string raw) : raw_(Clean(std::move(raw))) {
        components_ = Split(raw_, "/");
        components_.erase(components_.begin());
    }
    const std::vector<std::string>& Components() const {
        return components_;
    }
    const std::string& Raw() const {
        return raw_;
    }
    std::string Clean(std::string path) {
        if (path.empty()) {
            return "/";
        }
        if (path[0] != '/') {
            path = "/" + path;
        }
        return std::move(path);
    }

private:
    std::vector<std::string> components_;
    std::string raw_;
};