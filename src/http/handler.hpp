#pragma once
#include "request.hpp"
#include "response.hpp"
#include "../unique_function.hpp"

using Params = std::unordered_map<std::string, std::string>;

using HttpHandler = UniqueFunction<HttpResponse(HttpRequest, Params)>;

