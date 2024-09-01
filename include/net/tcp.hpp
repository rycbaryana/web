#pragma once
#include "io/socket_reader.hpp"
#include "io/socket_writer.hpp"
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <netdb.h>

namespace net {
std::pair<io::SocketReader, io::SocketWriter> ConnectTCP(const std::string& address, int port);

}  // namespace net