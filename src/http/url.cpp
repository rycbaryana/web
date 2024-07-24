#include <utils/text.hpp>
#include <utils/path.hpp>
#include <http/url.hpp>

// /path/to/smth?key1=val1;key2=val2#fragment
namespace http {
Url::Url(std::string raw) : raw_(std::move(raw)) {
    static constexpr std::string QueryDelimiter = ";";
    auto query_start = raw.find('?');
    auto fragment_start = raw.find('#');
    path_ = utils::Path(raw.substr(0, std::min(query_start, fragment_start)));
    if (query_start != std::string::npos && query_start + 1 < raw.size()) {
        std::string query_string =
            raw.substr(query_start + 1, fragment_start == std::string::npos
                                            ? std::string::npos
                                            : fragment_start - query_start - 1);
        args_ = utils::text::SplitKeyValue(query_string, QueryDelimiter, "=");
    }
    if (fragment_start != std::string::npos && fragment_start + 1 < raw.size()) {
        fragment_ = raw.substr(fragment_start + 1);
    }
}
}  // namespace http