#pragma once

#include <stdexcept>
#include <variant>

#include "err.hpp"
#include "result.hpp"

namespace res {

/** A type used for returning and propagating a value or an error.
 * This type could either have an ok status (success) which contains a value or
 * an error status (failure) which contains an error.
 * Use res::Result if the type does not need to contain a value when the status
 * is ok.
 * @tparam T The type of the value.
 *
 * @code
 * res::ResultOf<int> result_of_int = 32;
 * assert(result_of_int.is_ok());
 * assert(result_of_int.unwrap() == 32);
 *
 * result_of_int = res::Err("undefined error");
 * assert(result_of_int.is_err());
 * assert(result_of_int.unwrap_err() == "undefined error");
 * @endcode
 */
template <typename T>
class ResultOf {
 private:
  std::variant<T, Err> data;
  bool data_is_err;

 public:
  ResultOf() : ResultOf(Err("result-of is uninitialized")) {}
  ResultOf(const T& data) : data(data), data_is_err(false) {}
  ResultOf(const Err& err) : data(err), data_is_err(true) {}
  ResultOf(const ErrStream& err_stream)
      : data(err_stream.str()), data_is_err(true) {}

  template <typename U>
  explicit operator ResultOf<U>() const {
    if (data_is_err) return std::get<Err>(data);
    return static_cast<U>(std::get<T>(data));
  }

  operator Result() const {
    if (data_is_err) return std::get<Err>(data);
    return Ok();
  }

  template <typename U>
  ResultOf<U> as() const {
    if (data_is_err) return std::get<Err>(data);
    return static_cast<U>(std::get<T>(data));
  }

  bool is_ok() const { return !data_is_err; }
  bool is_err() const { return data_is_err; }

  const T& unwrap() const {
    if (data_is_err)
      throw std::runtime_error("unable to unwrap content of error result-of");
    return std::get<T>(data);
  }

  const Err& unwrap_err() const {
    if (!data_is_err)
      throw std::runtime_error("unable to unwrap error of ok result-of");
    return std::get<Err>(data);
  }
};
}  // namespace res
