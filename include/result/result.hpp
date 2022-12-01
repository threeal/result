#pragma once

#include "internal/ok.hpp"
#include <exception>
#include <optional>
#include <string>

namespace res {

class Result {
 private:
  std::optional<std::string> opt_err_msg;
 public:
  Result(const internal::Ok& ok) {}

  template<typename U>
  Result(const U& err_msg) : opt_err_msg(err_msg) {}

  bool is_ok() const { return !opt_err_msg.has_value(); }
  bool is_err() const { return opt_err_msg.has_value(); }

  std::string unwrap_err() const {
    if (!opt_err_msg.has_value()) throw std::runtime_error("is ok");
    return opt_err_msg.value();
  }
};
}
