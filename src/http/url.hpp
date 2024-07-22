#pragma once
#include <string>
#include <unordered_map>
#include "../io/utils.hpp"
#include "../path.hpp"

// /path/to/smth?key1=val1;key2=val2#fragment
struct Url {
    static constexpr std::string QueryDelimiter = ";";
public:
    Url() = default;
    Url(const std::string& raw) {
        auto query_start = raw.find('?');
        auto fragment_start = raw.find('#');
        path = Path(raw.substr(0, std::min(query_start, fragment_start)));
        if (query_start != std::string::npos && query_start + 1 < raw.size()) {
            std::string query_string = raw.substr(query_start + 1, fragment_start == std::string::npos ? std::string::npos : fragment_start - query_start - 1);
            query = SplitKeyValue(query_string, QueryDelimiter, "=");
        }
        if (fragment_start != std::string::npos && fragment_start + 1 < raw.size()) {
            fragment = raw.substr(fragment_start + 1);
        }
    }
    Path path;
    std::unordered_map<std::string, std::string> query;
    std::string fragment;
};