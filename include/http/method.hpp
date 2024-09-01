#pragma once
#include <string>
namespace http {
enum class HttpMethod { GET, POST, DELETE, PUT };
std::string ToString(HttpMethod method);
}  // namespace http