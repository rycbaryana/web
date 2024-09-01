#pragma once
#include <unordered_map>
#include <utils/path.hpp>
#include <utils/str_hash.hpp>
namespace http {
class Url {
public:
    using ArgsContainer = std::unordered_map<std::string, std::string, utils::StringHash>;
    Url() = default;

    explicit Url(std::string raw);

    const std::string& Raw() const& {
        return raw_;
    }

    const utils::Path& Path() const& {
        return path_;
    }
    const ArgsContainer& Args() const& {
        return args_;
    }
    std::string_view Fragment() const {
        return fragment_;
    }
    std::string_view Host() const {
        return host_;
    }
    std::string_view Schema() const {
        return scheme_;
    }
    std::string_view Request() const {
        return request_;
    }
    uint16_t Port() const {
        return port_;
    }
    static const std::unordered_map<std::string, uint16_t, utils::StringHash, std::equal_to<>> ports;
private:
    std::string raw_;
    std::string_view scheme_;
    std::string_view host_;
    std::string_view request_;
    utils::Path path_;
    ArgsContainer args_;
    std::string_view fragment_;
    uint16_t port_;
};
}  // namespace http