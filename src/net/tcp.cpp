#include "net/tcp.hpp"
namespace net {

std::pair<io::SocketReader, io::SocketWriter> ConnectTCP(const std::string& address, int port) {
    struct addrinfo* servinfo;
    if (int status = getaddrinfo(address.c_str(), std::to_string(port).c_str(), nullptr, &servinfo);
        status != 0) {
        std::cerr << "getaddrinfo error: " << gai_strerror(status) << '\n';
        exit(1);
    }
    int sockfd = socket(PF_INET, servinfo->ai_socktype, servinfo->ai_protocol);
    if (int status = connect(sockfd, servinfo->ai_addr, servinfo->ai_addrlen); status != 0) {
        std::cerr << "connect error: " << strerror(errno);
        exit(1);
    }
    freeaddrinfo(servinfo);
    return std::make_pair(io::SocketReader(sockfd), io::SocketWriter(sockfd));
}

}  // namespace client