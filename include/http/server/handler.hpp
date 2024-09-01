#pragma once
#include "http/respone.hpp"
#include "http/request.hpp"
#include "utils/unique_function.hpp"
#include "utils/str_hash.hpp"

namespace http {
    using Params = std::unordered_map<std::string, std::string, utils::StringHash>;

    using Handler = utils::UniqueFunction<Response(Request, Params)>;
}  // namespace http
