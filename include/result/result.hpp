#pragma once

#include <error/error.hpp>
#include <variant>

#include "ok.hpp"

namespace res {

/** A type used for returning and propagating a value or an error.
 * This type could either have an ok status (success) which contains a value or
 * an error status (failure) which contains an error.
 * is ok.
 * @tparam T The type of the value.
 *
 * @code
 * res::Result<int> result_of_int = 32;
 * assert(result_of_int.is_ok());
 * assert(result_of_int.unwrap() == 32);
 *
 * result_of_int = error::Error("undefined error");
 * assert(result_of_int.is_err());
 * assert(result_of_int.unwrap_err().message == "undefined error");
 * @endcode
 */
template <typename T = Ok>
class Result {
 private:
  std::variant<T, error::Error> data;
  bool data_is_err;

 public:
  /** Construct a new empty result-of.
   * Defaults to contain an error.
   *
   * @code
   * res::Result<int> result_of_int;
   * assert(result_of_int.is_err());
   * @endcode
   */
  Result() : Result(error::Error("result-of is uninitialized")) {}

  /** Construct a new ok result-of (success) that contains a value.
   * @param val The value.
   *
   * @code
   * res::Result<int> result_of_int = 32;
   * assert(result_of_int.is_ok());
   * @endcode
   */
  Result(const T& val) : data(val), data_is_err(false) {}

  /** Construct a new error result-of (failure).
   * @param err The error status.
   *
   * @code
   * res::Result<int> result_of_int = error::Error("undefined error");
   * assert(result_of_int.is_err());
   * @endcode
   */
  Result(const error::Error& err) : data(err), data_is_err(true) {}

  /** Explicitly convert into another result-of with a different value type.
   * If the status is ok, the value data will be cast into the target value
   * type. See res::Result::as.
   * @tparam U the target value type.
   *
   * @code
   * res::Result<int> result_of_int = 32;
   * auto result_of_float = static_cast<res::Result<float>>(result_of_int);
   * assert(result_of_float.unwrap() == 32);
   * @endcode
   */
  template <typename U>
  explicit operator Result<U>() const {
    if (data_is_err) return std::get<error::Error>(data);
    return static_cast<U>(std::get<T>(data));
  }

  /** Convert into another result-of with a different value type.
   * If the status is ok, the value data will be cast into the target value
   * type.
   * @tparam U The target value type.
   * @return The converted result-of.
   *
   * @code
   * res::Result<int> result_of_int = 32;
   * res::Result<float> result_of_float = result_of_int.as<float>();
   * assert(result_of_float.unwrap() == 32);
   * @endcode
   */
  template <typename U>
  Result<U> as() const {
    if (data_is_err) return std::get<error::Error>(data);
    return static_cast<U>(std::get<T>(data));
  }

  /** Check if the status is ok.
   * @return `true` if the status is ok.
   */
  bool is_ok() const { return !data_is_err; }

  /** Check if the status is failed.
   * @return `true` if the status is failed.
   */
  bool is_err() const { return data_is_err; }

  /** Get the value data if the status is ok.
   * This function will throw an exception if the status is not ok.
   * @return The value data.
   * @exception error::Error The status is not ok.
   *
   * @code
   * res::Result<int> result_of_int = 32;
   * assert(result_of_int.unwrap() == 32);
   * @endcode
   *
   * @code{.cpp}
   * res::Result<int> result_of_int = error::Error("undefined error");
   * result_of_int.unwrap();  // throws exception
   * @endcode
   */
  const T& unwrap() const {
    if (data_is_err)
      throw error::Error("Unable to unwrap content of error result-of");
    return std::get<T>(data);
  }

  /** Get the error data if the status is failed.
   * This function will throw an exception if the status is not failed.
   * @return The error data.
   * @exception error::Error The status is not failed.
   *
   * @code
   * res::Result<int> result_of_int = error::Error("undefined error");
   * assert(result_of_int.unwrap_err().message == "undefined error");
   * @endcode
   *
   * @code{.cpp}
   * res::Result<int> result_of_int = 32;
   * result_of_int.unwrap_err();  // throws exception
   * @endcode
   */
  const error::Error& unwrap_err() const {
    if (!data_is_err)
      throw error::Error("Unable to unwrap error of ok result-of");
    return std::get<error::Error>(data);
  }
};
}  // namespace res
