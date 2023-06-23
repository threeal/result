#pragma once

#include <error/error.hpp>
#include <optional>

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
 * result = error::Error("undefined error");
 * assert(result.is_err());
 * assert(result.unwrap_err().message == "undefined error");
 * @endcode
 */
class Result {
 private:
  std::optional<error::Error> err_opt;

 public:
  /** Construct a new empty result.
   * Defaults to contain an error.
   *
   * @code
   * res::Result result;
   * assert(result.is_err());
   * @endcode
   */
  Result() : Result(error::Error("result is uninitialized")) {}

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
   * res::Result result = error::Error("undefined error");
   * assert(result.is_err());
   * @endcode
   */
  Result(const error::Error& err) : err_opt(err) {}

  /** Check if the status is ok.
   * @return `true` if the status is ok.
   */
  bool is_ok() const { return !err_opt.has_value(); }

  /** Check if the status is failed.
   * @return `true` if the status is failed.
   */
  bool is_err() const { return err_opt.has_value(); }

  /** Get the error data if the status is failed.
   * This function will throw an exception if the status is not failed.
   * @return The error data.
   * @exception error::Error The status is not failed.
   *
   * @code
   * res::Result result = error::Error("undefined error");
   * assert(result.unwrap_err().message == "undefined error");
   * @endcode
   *
   * @code{.cpp}
   * res::Result result = res::Ok();
   * result.unwrap_err();  // throws exception
   * @endcode
   */
  const error::Error& unwrap_err() const {
    if (!err_opt.has_value())
      throw error::Error("Unable to unwrap error of ok result");
    return err_opt.value();
  }
};
}  // namespace res
