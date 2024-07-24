#include <sys/socket.h>
#include <io/reader.hpp>
#include <stdexcept>
namespace io {
std::string_view SocketReader::Read() {
    auto read = recv(socket_, buf, kBufSize, 0);
    if (read == -1) {
        throw std::runtime_error("read failed");
    }
    return std::string_view(buf, read);
}
}  // namespace io