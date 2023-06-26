#pragma once

#include <error/error.hpp>
#include <variant>

#include "ok.hpp"

namespace result {

/**
 * @brief Represents a result type that can contain either a value or an error.
 * @tparam T The type of the value.
 *
 * The `Result` class is used to handle operations that can produce either a
 * value or an error. It provides a way to propagate and handle errors in a
 * controlled manner.
 *
 * @code{.cpp}
 * result::Result<int> res = 32;
 * assert(res.is_ok());
 * assert(res.unwrap() == 32);
 *
 * res = error::Error("undefined error");
 * assert(res.is_err());
 * assert(res.unwrap_err().message == "undefined error");
 * @endcode
 */
template <typename T = Ok>
class Result {
 private:
  std::variant<T, error::Error> data;
  bool data_is_err;

 public:
  /**
   * @brief Constructs a new empty result.
   *
   * This constructor creates a new result object that is initialized with an
   * error by default.
   *
   * @code{.cpp}
   * result::Result<int> res;
   * assert(res.is_err());
   * @endcode
   */
  Result() : Result(error::Error("result is uninitialized")) {}

  /**
   * @brief Constructs a new result that contains a value.
   * @param val The value.
   *
   * @code{.cpp}
   * result::Result<int> res = 32;
   * assert(res.is_ok());
   * @endcode
   */
  Result(const T& val) : data(val), data_is_err(false) {}

  /**
   * @brief Constructs a new result that contains an error.
   * @param err The error.
   *
   * @code{.cpp}
   * result::Result<int> res = error::Error("undefined error");
   * assert(res.is_err());
   * @endcode
   */
  Result(const error::Error& err) : data(err), data_is_err(true) {}

  /**
   * @brief Explicitly converts the result into another result with a different
   * value type.
   * @tparam U The target value type.
   *
   * This conversion operator allows explicit casting of the result into another
   * result with a different value type. If the result contains a value, that
   * value will be explicitly casted into the target value type. If the result
   * contains an error, copy that error. See also `result::Result::as`.
   *
   * @code{.cpp}
   * result::Result<int> int_res = 32;
   * auto float_res = static_cast<result::Result<float>>(int_res);
   * assert(float_res.is_ok());
   * assert(float_res.unwrap() == 32);
   * @endcode
   *
   * @code{.cpp}
   * result::Result<int> int_res = error::Error("undefined error");
   * auto float_res = static_cast<result::Result<float>>(int_res);
   * assert(float_res.is_err());
   * assert(float_res.unwrap_err().message == "undefined error");
   * @endcode
   */
  template <typename U>
  explicit operator Result<U>() const {
    if (data_is_err) return std::get<error::Error>(data);
    return static_cast<U>(std::get<T>(data));
  }

  /**
   * @brief Converts the result into another result with a different value type.
   * @tparam U The target value type.
   * @return A converted result of the target type.
   *
   * This function allows converting the result into another result with a
   * different value type. If the result contains a value, it will be explicitly
   * casted into the target value type. If the result contains an error, copy
   * that error.
   *
   * @code{.cpp}
   * result::Result<int> int_res = 32;
   * result::Result<float> float_res = int_res.as<float>();
   * assert(float_res.is_ok());
   * assert(float_res.unwrap() == 32);
   * @endcode
   *
   * @code{.cpp}
   * result::Result<int> int_res = error::Error("undefined error");
   * result::Result<float> float_res = int_res.as<float>();
   * assert(float_res.is_err());
   * assert(float_res.unwrap_err().message == "undefined error");
   * @endcode
   */
  template <typename U>
  Result<U> as() const {
    if (data_is_err) return std::get<error::Error>(data);
    return static_cast<U>(std::get<T>(data));
  }

  /**
   * @brief Checks if the result contains a value.
   * @return `true` if the result contains a value, `false` otherwise.
   */
  bool is_ok() const { return !data_is_err; }

  /**
   * @brief Checks if the result contains an error.
   * @return `true` if the result contains an error, `false` otherwise.
   */
  bool is_err() const { return data_is_err; }

  /**
   * @brief Gets the value from the result.
   * @return A constant reference to the stored value.
   * @throws error::Error If the result does not contain a value.
   *
   * This function retrieves the value stored in the result object. If the
   * result contains a value, it returns a constant reference to the value. If
   * the result does not contain a value, it throws an exception of type
   * `error::Error`.
   *
   * @code{.cpp}
   * result::Result<int> res = 32;
   * assert(res.unwrap() == 32);
   * @endcode
   *
   * @code{.cpp}
   * result::Result<int> res = error::Error("undefined error");
   * res.unwrap();  // throws error::Error
   * @endcode
   */
  const T& unwrap() const {
    if (data_is_err) throw error::format("the result contains an error");
    return std::get<T>(data);
  }

  /**
   * @brief Gets the error from the result.
   * @return A constant reference to the stored error.
   * @throws error::Error If the result does not contain an error.
   *
   * This function retrieves the error stored in the result object. If the
   * result contains an error, it returns a constant reference to the error. If
   * the result does not contain an error, it throws an exception of type
   * `error::Error`.
   *
   * @code{.cpp}
   * result::Result<int> res = error::Error("undefined error");
   * assert(res.unwrap_err().message == "undefined error");
   * @endcode
   *
   * @code{.cpp}
   * result::Result<int> res = 32;
   * res.unwrap_err();  // throws error::Error
   * @endcode
   */
  const error::Error& unwrap_err() const {
    if (!data_is_err) throw error::Error("the result contains a value");
    return std::get<error::Error>(data);
  }
};
}  // namespace result
