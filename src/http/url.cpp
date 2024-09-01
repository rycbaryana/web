#include <utils/text.hpp>
#include <utils/path.hpp>
#include <http/url.hpp>
#include <charconv>
#include <iostream>
// /path/to/smth?key1=val1;key2=val2#fragment
namespace http {
const std::unordered_map<std::string, uint16_t, utils::StringHash, std::equal_to<>> Url::ports = {{"http", 80},
                                                                                 {"https", 443}};

Url::Url(std::string _raw) : raw_(std::move(_raw)) {
    static constexpr std::string QueryDelimiter = ";";
    auto query_start = raw_.find('?');
    auto fragment_start = raw_.find('#');
    size_t n = raw_.size();
    auto view = std::string_view(raw_);
    scheme_ = view.substr(0, view.find(':'));
    view.remove_prefix(scheme_.size() + 3);
    if (auto it = view.find(':'); it != std::string_view::npos) {
        host_ = view.substr(0, it);
        view.remove_prefix(host_.size() + 1);
        it = view.find('/');
        std::from_chars(view.begin(), view.begin() + it, port_);
        view.remove_prefix(it);
    } else {
        host_ = view.substr(0, view.find('/'));
        view.remove_prefix(host_.size());
        if (auto it = ports.find(scheme_); it != ports.end()) {
            port_ = it->second;
        } else {
            std::cerr << "Unknown scheme! " << scheme_ << '\n';
        }
    }
    request_ = view;
    path_ = utils::Path(std::string(view.substr(
        0, std::min(query_start, fragment_start))));  // todo std::string -> std::string_view
    if (query_start != std::string::npos && query_start + 1 < raw_.size()) {
        std::string query_string =
            raw_.substr(query_start + 1, fragment_start == std::string::npos
                                             ? std::string::npos
                                             : fragment_start - query_start - 1);
        args_ = utils::text::SplitKeyValue(query_string, QueryDelimiter, "=");
    }
    if (fragment_start != std::string::npos && fragment_start + 1 < raw_.size()) {
        fragment_ = raw_.substr(fragment_start + 1);
    }
}
}  // namespace http