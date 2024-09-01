#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "str_hash.hpp"

namespace utils::text {
template <typename String>
std::vector<std::string> Split(const String& data, std::string delimiter) {
    size_t index = 0;
    size_t prev = 0;
    std::vector<std::string> result;
    if (data.empty()) {
        return result;
    }
    while (index != std::string::npos) {
        index = data.find(delimiter, prev);
        result.push_back(std::string(data.substr(prev, index - prev)));
        prev = index + delimiter.size();
    }
    return result;


}

template <typename String>
std::unordered_map<std::string, std::string, utils::StringHash> SplitKeyValue(const String& data,
                                                           std::string delimiter,
                                                           std::string key_value_delimiter) {
    std::unordered_map<std::string, std::string, utils::StringHash> map;
    auto pairs = Split(data, delimiter);
    for (auto& pair_str : pairs) {
        auto pair = Split(pair_str, key_value_delimiter);
        if (pair.size() < 2) {
            return map;
        }
        map[pair[0]] = pair[1];
    }
    return map;
}

inline size_t LongestPrefix(const std::string& a, const std::string& b) {
    auto min = std::min(a.size(), b.size());
    for (int i = 0; i < min; ++i) {
        if (a[i] != b[i]) {
            return i;
        }
    }
    return min;
}
}
