#include <sys/socket.h>
#include <io/writer.hpp>
#include <stdexcept>
namespace io {
size_t SocketWriter::Write(std::string_view data) {
    auto sent = send(socket_, data.data(), data.size(), 0);
    if (sent == -1) {
        throw std::runtime_error("send failed");
    }
    return sent;
}
}  // namespace io