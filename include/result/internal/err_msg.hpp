#pragma once

#include <string>

namespace res::internal {

using ErrMsg = std::string;
const ErrMsg uninitialized_err_msg = "result is uninitialized";
}
