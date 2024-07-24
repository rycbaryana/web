#include <string>
#include <vector>
#include <utils/text.hpp>
#include <utils/path.hpp>
namespace utils {
std::string Clean(std::string path) {
    if (path.empty()) {
        return "/";
    }
    if (path[0] != '/') {
        path = "/" + path;
    }
    return std::move(path);
}
Path::Path(std::string raw) : raw_(Clean(std::move(raw))) {
    components_ = utils::text::Split(raw_, "/");
    components_.erase(components_.begin());
}

}  // namespace utils