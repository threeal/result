#pragma once

#include <stdexcept>
#include <variant>

#include "err.hpp"
#include "result.hpp"

namespace res {

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
