#pragma once
#include <string_view>

namespace io {
class SocketReader {
    static constexpr size_t kBufSize = 16384;
public:
    explicit SocketReader(int socket) : socket_(socket) {
    }
    std::string_view Read();

private:
    char buf[kBufSize]{};
    int socket_;
};
}  // namespace io
