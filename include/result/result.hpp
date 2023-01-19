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
  /** Construct a new empty result.
   * Defaults to contain an error.
   *
   * @code
   * res::Result result;
   * assert(result.is_err());
   * @endcode
   */
  Result() : Result(Err("result is uninitialized")) {}

  /** Construct a new ok result (success).
   * @param ok The ok status.
   *
   * @code
   * res::Result result = res::Ok();
   * assert(result.is_ok());
   * @endcode
   */
  Result([[maybe_unused]] const Ok& ok) {}

  /** Construct a new error result (failure).
   * @param err The error status.
   *
   * @code
   * res::Result result = res::Err("undefined error");
   * assert(result.is_err());
   * @endcode
   */
  Result(const Err& err) : err_opt(err) {}

  /** Construct a new error result (failure) using an error stream.
   * @param err_stream The error stream.
   *
   * @code
   * res::Result result = res::ErrStream() << 404 << " not found";
   * assert(result.is_err());
   * assert(result.unwrap_err() == "404 not found");
   * @endcode
   */
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
