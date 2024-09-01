#include <net/base_server.hpp>
#include <stdexcept>
namespace net {
BaseServer::BaseServer(int port) {
    server_fd_ = socket(PF_INET, SOCK_STREAM, 0);
    if (server_fd_ < 0) {
        throw std::runtime_error("Failed to create server socket");
    }
    int reuse = 1;
    if (setsockopt(server_fd_, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        throw std::runtime_error("setsockopt failed");
    }

    addr_.sin_family = AF_INET;
    addr_.sin_addr.s_addr = INADDR_ANY;
    addr_.sin_port = htons(port);

    if (bind(server_fd_, (struct sockaddr *)&addr_, sizeof(addr_)) != 0) {
        throw std::runtime_error("Failed to bind to port " + std::to_string(port));
    }
}

void BaseServer::Listen(int backlog) {
    if (listen(server_fd_, backlog) != 0) {
        throw std::runtime_error("listen failed");
    }
}

std::pair<io::SocketReader, io::SocketWriter> BaseServer::Accept() {
    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);
    int client_socket =
        accept(server_fd_, (struct sockaddr *)&client_addr, (socklen_t *)&client_addr_len);
    return {io::SocketReader(client_socket), io::SocketWriter(client_socket)};
}

}  // namespace net