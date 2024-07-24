#pragma once
#include <vector>
#include <string>
namespace utils {
class Path {
public:
    Path() = default;
    Path(std::string raw);

    const std::vector<std::string>& Components() const& {
        return components_;
    }
    const std::string& Raw() const& {
        return raw_;
    }

private:
    std::string raw_;
    std::vector<std::string> components_;
};
}  // namespace utils
