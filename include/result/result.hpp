#pragma once

#include "internal/err.hpp"
#include "internal/ok.hpp"
#include <exception>
#include <optional>

namespace res {

class Result {
 private:
  std::optional<internal::Err> err_opt;
 public:
  Result() : err_opt(internal::uninitialized_err) {}
  Result(const internal::Ok& ok) {}
  Result(const internal::Err& err) : err_opt(err) {}

  bool is_ok() const { return !err_opt.has_value(); }
  bool is_err() const { return err_opt.has_value(); }

  internal::Err unwrap_err() const {
    if (!err_opt.has_value()) throw std::runtime_error("is ok");
    return err_opt.value();
  }  // LCOV_EXCL_LINE
};
}
