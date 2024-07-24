#pragma once
#include <string>
namespace http {
enum class HttpMethod { UNSPECIFIED, GET, POST, DELETE, PUT };
std::string ToString(HttpMethod method);
}  // namespace http