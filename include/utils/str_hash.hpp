#pragma once
#include <string_view>
namespace utils {
struct StringHash {
    using is_transparent = void;

    size_t operator()(std::string_view str) const {
        return std::hash<std::string_view>{}(str);
    }
};
}  // namespace utils
