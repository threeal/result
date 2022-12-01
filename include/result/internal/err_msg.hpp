#pragma once

#include <memory>
#include <string>

namespace res::internal {

using ErrMsg = std::string;
using ErrMsgPtr = std::shared_ptr<ErrMsg>;
}
