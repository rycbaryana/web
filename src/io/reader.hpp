#pragma once
#include <sys/socket.h>

#include <stdexcept>
#include <string_view>

class SocketReader {
    static constexpr size_t kBufSize = 16384;

public:
    SocketReader(int socket) : socket_(socket) {
    }
    std::string_view Read() {
        auto read = recv(socket_, buf, kBufSize, 0);
        if (read == -1) {
            throw std::runtime_error("read failed");
        }
        return std::string_view(buf, read);
    }

private:
    char buf[kBufSize];
    int socket_;
};