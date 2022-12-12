#pragma once

#include <optional>
#include <stdexcept>

#include "err.hpp"
#include "ok.hpp"

namespace res {

class Result {
 private:
  std::optional<Err> err_opt;

 public:
  Result() : Result(Err("result is uninitialized")) {}
  Result(const Ok& ok) {}
  Result(const Err& err) : err_opt(err) {}

  bool is_ok() const { return !err_opt.has_value(); }
  bool is_err() const { return err_opt.has_value(); }

  const Err& unwrap_err() const {
    if (!err_opt.has_value())
      throw std::runtime_error("unable to unwrap error of ok result");
    return err_opt.value();
  }
};
}  // namespace res
