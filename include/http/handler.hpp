#pragma once
#include "respone.hpp"
#include "request.hpp" 
#include <utils/unique_function.hpp>
#include <utils/str_hash.hpp>

namespace http {
    using Params = std::unordered_map<std::string, std::string, utils::StringHash>;

    using Handler = utils::UniqueFunction<Response(Request, Params)>;
}  // namespace http
