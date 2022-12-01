#pragma once

#include "internal/error.hpp"
#include "internal/ok.hpp"
#include <optional>
#include <exception>

namespace res {

class Result {
 private:
  std::optional<internal::Error> error;
 public:
  Result(const internal::Ok& ok) {}
  Result(const internal::Error& err) : error(err) {}
  bool is_ok() const { return !error.has_value(); }
  bool is_err() const { return error.has_value(); }
};
}
