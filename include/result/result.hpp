#pragma once

#include "internal/err_msg.hpp"
#include "internal/ok.hpp"
#include <exception>
#include <memory>

namespace res {

class Result {
 private:
  internal::ErrMsgPtr err_msg_ptr;
 public:
  Result() : err_msg_ptr(internal::uninitialized_err_msg_ptr) {}
  Result(const internal::Ok& ok) {}
  Result(const internal::ErrMsgPtr& err_msg_ptr) : err_msg_ptr(err_msg_ptr) {}

  template<typename E>
  Result(const E& err_msg) : err_msg_ptr(std::make_shared<internal::ErrMsg>(err_msg)) {}

  bool is_ok() const { return !err_msg_ptr; }
  bool is_err() const { return (bool)err_msg_ptr; }

  internal::ErrMsg unwrap_err() const {
    if (!err_msg_ptr) throw std::runtime_error("is ok");
    return *err_msg_ptr;
  }  // LCOV_EXCL_LINE
};
}
