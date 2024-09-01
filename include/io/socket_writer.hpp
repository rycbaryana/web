#pragma once
#include <string_view>
namespace io {
class SocketWriter {
public:
    explicit SocketWriter(int socket) : socket_(socket) {
    }
    size_t Write(std::string_view data);

private:
    int socket_;
};
}  // namespace io
