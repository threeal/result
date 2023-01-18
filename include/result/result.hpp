#pragma once

#include <optional>
#include <stdexcept>

#include "err.hpp"
#include "ok.hpp"

namespace res {

/** A type used for returning and propagating an error.
 * This type could either have an ok status (success) which does not contain an
 * error or have an error status (failure) which contains an error.
 * Use res::ResultOf if the type needs to contain a value when the status is ok.
 *
 * @code
 * res::Result result = res::Ok();
 * assert(result.is_ok());
 *
 * result = res::Err("undefined error");
 * assert(result.is_err());
 * assert(result.unwrap_err() == "undefined error");
 * @endcode
 */
class Result {
 private:
  std::optional<Err> err_opt;

 public:
  Result() : Result(Err("result is uninitialized")) {}
  Result(const Ok&) {}
  Result(const Err& err) : err_opt(err) {}
  Result(const ErrStream& err_stream) : err_opt(err_stream.str()) {}

  bool is_ok() const { return !err_opt.has_value(); }
  bool is_err() const { return err_opt.has_value(); }

  const Err& unwrap_err() const {
    if (!err_opt.has_value())
      throw std::runtime_error("unable to unwrap error of ok result");
    return err_opt.value();
  }
};
}  // namespace res
