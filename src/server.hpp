#pragma once
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>
#include <string>

#include "io/reader.hpp"
#include "io/writer.hpp"

class Server {
 public:
  Server(int port) {
    server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd_ < 0) {
      throw std::runtime_error("Failed to create server socket");
    }
    int reuse = 1;
    if (setsockopt(server_fd_, SOL_SOCKET, SO_REUSEADDR, &reuse,
                   sizeof(reuse)) < 0) {
      throw std::runtime_error("setsockopt failed");
    }

    addr_.sin_family = AF_INET;
    addr_.sin_addr.s_addr = INADDR_ANY;
    addr_.sin_port = htons(port);

    if (bind(server_fd_, (struct sockaddr *)&addr_, sizeof(addr_)) != 0) {
      throw std::runtime_error("Failed to bind to port " +
                               std::to_string(port));
    }
  }
  Server(std::string address, int port) {
    //
  }

  void Listen(int backlog = 32) {
    if (listen(server_fd_, backlog) != 0) {
      throw std::runtime_error("listen failed");
    }
  }

  std::pair<SocketReader, SocketWriter> Accept() {
    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);
    int client_socket = accept(server_fd_, (struct sockaddr *)&client_addr,
                               (socklen_t *)&client_addr_len);
    return {SocketReader(client_socket), SocketWriter(client_socket)};
  }
  ~Server() {
    close(server_fd_);
  }

 private:
  struct sockaddr_in addr_;
  int server_fd_;
};
