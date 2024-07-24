#pragma once
#include <unordered_map>
#include <utils/path.hpp>
namespace http {
class Url {
public:
    Url() = default;

    Url(std::string raw);

    const std::string& Raw() const& {
        return raw_;
    }

    const utils::Path& Path() const& {
        return path_;
    }
    const std::unordered_map<std::string, std::string>& Args() const& {
        return args_;
    }
    std::string_view Fragment() const {
        return fragment_;
    }
    std::string_view Host() const {
        return host_;
    }

private:
    std::string raw_;
    utils::Path path_;
    std::unordered_map<std::string, std::string> args_;
    std::string_view fragment_;
    std::string_view host_;
};
}  // namespace http