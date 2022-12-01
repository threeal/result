#pragma once

#include "internal/ok.hpp"
#include <optional>
#include <exception>

namespace res {

class Result {
 private:
  std::optional<std::exception> error;
 public:
  Result(const internal::Ok& ok) {}
  Result(const std::exception& err) : error(err) {}
  bool is_ok() const { return !error.has_value(); }
  bool is_err() const { return error.has_value(); }
};
}
