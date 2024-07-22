#pragma once
#include <sys/socket.h>

#include <stdexcept>

class SocketWriter {
 public:
  SocketWriter(int socket) : socket_(socket) {}
  size_t Write(std::string data) {
    auto sent = send(socket_, data.data(), data.size(), 0);
    if (sent == -1) {
      throw std::runtime_error("send failed");
    }
    return sent;
  }

 private:
  int socket_;
};