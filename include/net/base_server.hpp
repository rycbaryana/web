#pragma once
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>

#include "io/reader.hpp"
#include "io/writer.hpp"

namespace net {
class BaseServer {
public:
    BaseServer(int port);
    BaseServer(std::string address, int port);

    void Listen(int backlog = 32);

    std::pair<io::SocketReader, io::SocketWriter> Accept();
    
    ~BaseServer() {
        close(server_fd_);
    }

private:
    struct sockaddr_in addr_;
    int server_fd_;
};

}  // namespace net
