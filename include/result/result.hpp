#pragma once

#include "internal/ok.hpp"
#include <optional>
#include <string>

namespace res {

class Result {
 private:
  std::optional<std::string> error;
 public:
  Result(const internal::Ok& ok) {}

  template<typename U>
  Result(const U& err) : error(err) {}

  bool is_ok() const { return !error.has_value(); }
  bool is_err() const { return error.has_value(); }
};
}
