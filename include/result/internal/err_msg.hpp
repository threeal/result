#pragma once

#include <memory>
#include <string>

namespace res::internal {

using ErrMsg = std::string;
using ErrMsgPtr = std::shared_ptr<ErrMsg>;

ErrMsgPtr uninitialized_err_msg_ptr = std::make_shared<ErrMsg>("result is uninitialized");
}
