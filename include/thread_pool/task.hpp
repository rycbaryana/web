#pragma once
#include <utils/unique_function.hpp>

namespace threads {
using Task = utils::UniqueFunction<void()>;
}
