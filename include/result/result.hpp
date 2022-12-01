#pragma once

#include "internal/ok.hpp"
#include <optional>

namespace res {

template<typename E>
class Result {
 private:
  std::optional<E> error;
 public:
  Result(const E& err) : error(err) {}
  Result(const internal::Ok& ok) {}
  bool is_ok() const { return !error.has_value(); }
  bool is_err() const { return error.has_value(); }
};
}
