#pragma once

#include <errors/error.hpp>
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
 * Use the `Result` class when you have operations that can succeed and return
 * a value, or fail and return an error. This allows you to handle both cases
 * explicitly and make informed decisions based on the outcome.
 *
 * @code{.cpp}
 * class Image;
 *
 * result::Result<Image> load_image(const std::filesystem::path& path);
 *
 * int main() {
 *   const auto res = load_image(image_path);
 *   if (res.is_ok()) {
 *     const auto& image = res.unwrap();
 *     // Do something with the image.
 *   } else {
 *     const auto& error = res.unwrap_err();
 *     // Handle the error case.
 *   }
 * }
 * @endcode
 */
template <typename T = Ok>
class [[nodiscard]] Result {
 private:
  std::variant<T, errors::Error> data;
  bool data_is_err;

 public:
  /**
   * @brief Constructs a new empty result.
   *
   * This constructor creates a new result object that is initialized with an
   * error by default.
   *
   * @code{.cpp}
   * result::Result<> res;
   * assert(res.is_err());
   *
   * // Print "the result is uninitialized".
   * std::cout << res.unwrap_err().what() << std::endl;
   * @endcode
   */
  Result();

  /**
   * @brief Constructs a new result that contains a value.
   * @param val The value.
   *
   * @code{.cpp}
   * result::Result<int> res = 200;
   * assert(res.is_ok());
   *
   * // Print "200".
   * std::cout << res.unwrap() << std::endl;
   * @endcode
   */
  Result(const T& val);

  /**
   * @brief Constructs a new result that contains an error.
   * @param err The error.
   *
   * @code{.cpp}
   * result::Result<int> res = errors::make("undefined error");
   * assert(res.is_err());
   *
   * // Print "undefined error".
   * std::cout << res.unwrap_err().what() << std::endl;
   * @endcode
   */
  Result(const errors::Error& err);

  /**
   * @brief Explicitly converts the result into another result with a different
   * value type.
   * @tparam U The target value type.
   * @return A converted result.
   *
   * This conversion operator allows explicit casting of the result into another
   * result with a different value type. If the result contains a value, that
   * value will be explicitly casted into the target value type. If the result
   * contains an error, the error will be copied. See also `result::Result::as`.
   *
   * @code{.cpp}
   * using IntRes = result::Result<int>;
   *
   * result::Result<double> square_root(double val) {
   *   if (value < 0) return errors::make("value must be positive");
   *   return std::sqrt(value);
   * }
   *
   * int main() {
   *   IntRes res = static_cast<IntRes>(square_root(100.0));
   *   assert(res.is_ok());
   *
   *   // Print "10".
   *   std::cout << res.unwrap() << std::endl;
   *
   *   res = static_cast<IntRes>(square_root(-100.0));
   *   assert(res.is_err());
   *
   *   // Print "value must be positive".
   *   std::cout << res.unwrap_err().what() << std::endl;
   * }
   * @endcode
   */
  template <typename U>
  explicit operator Result<U>() const;

  /**
   * @brief Converts the result into another result with a different value type.
   * @tparam U The target value type.
   * @return A converted result.
   *
   * This function allows converting the result into another result with a
   * different value type. If the result contains a value, it will be explicitly
   * casted into the target value type. If the result contains an error, the
   * error will be copied.
   *
   * @code{.cpp}
   * result::Result<double> square_root(double val) {
   *   if (value < 0) return errors::make("value must be positive");
   *   return std::sqrt(value);
   * }
   *
   * int main() {
   *   result::Result<int> res = square_root(100.0).as<int>();
   *   assert(res.is_ok());
   *
   *   // Print "10".
   *   std::cout << res.unwrap() << std::endl;
   *
   *   res = square_root(-100.0).as<int>();
   *   assert(res.is_err());
   *
   *   // Print "value must be positive".
   *   std::cout << res.unwrap_err().what() << std::endl;
   * }
   * @endcode
   */
  template <typename U>
  Result<U> as() const;

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
   * @throws errors::Error If the result does not contain a value.
   *
   * This function retrieves the value stored in the result object. If the
   * result contains a value, it returns a constant reference to the value. If
   * the result does not contain a value, it throws an exception of type
   * `errors::Error`.
   *
   * @code{.cpp}
   * result::Result<int> res = 200;
   *
   * // Print "200".
   * std::cout << res.unwrap() << std::endl;
   *
   * res = errors::make("undefined error");
   *
   * // Throws `errors::Error`.
   * // std::cout << res.unwrap() << std::endl;
   * @endcode
   */
  const T& unwrap() const;

  /**
   * @brief Gets the error from the result.
   * @return A constant reference to the stored error.
   * @throws errors::Error If the result does not contain an error.
   *
   * This function retrieves the error stored in the result object. If the
   * result contains an error, it returns a constant reference to the error. If
   * the result does not contain an error, it throws an exception of type
   * `errors::Error`.
   *
   * @code{.cpp}
   * result::Result<int> res = errors::make("undefined error");
   *
   * // Print "undefined error".
   * std::cout << res.unwrap_err().what() << std::endl;
   *
   * res = 200;
   *
   * // Throws `errors::Error`.
   * // std::cout << res.unwrap_err().what() << std::endl;
   * @endcode
   */
  const errors::Error& unwrap_err() const;
};

}  // namespace result

#include "result.ipp"
