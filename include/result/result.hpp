#pragma once

#include "internal/err_msg.hpp"
#include "internal/ok.hpp"
#include <exception>
#include <optional>

namespace res {

class Result {
 private:
  std::optional<internal::ErrMsg> err_msg_opt;
 public:
  Result() : err_msg_opt(internal::uninitialized_err_msg) {}
  Result(const internal::Ok& ok) {}
  Result(const internal::ErrMsg& err_msg) : err_msg_opt(err_msg) {}
  Result(const char* err_msg) : err_msg_opt(err_msg) {}

  bool is_ok() const { return !err_msg_opt.has_value(); }
  bool is_err() const { return err_msg_opt.has_value(); }

  internal::ErrMsg unwrap_err() const {
    if (!err_msg_opt.has_value()) throw std::runtime_error("is ok");
    return err_msg_opt.value();
  }  // LCOV_EXCL_LINE
};
}
