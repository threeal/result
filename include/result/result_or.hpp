#pragma once

#include "err.hpp"
#include <stdexcept>
#include <variant>

namespace res {

template<typename T>
class ResultOr {
 private:
  std::variant<T, Err> data;
  bool data_is_err;
 public:
  ResultOr() : ResultOr(Err("result-or is uninitialized")) {}
  ResultOr(const T& data) : data(data), data_is_err(false) {}
  ResultOr(const Err& err) : data(err), data_is_err(true) {}

  bool is_ok() const { return !data_is_err; }
  bool is_err() const { return data_is_err; }

  const T& unwrap() const {
    if (data_is_err)
      throw std::runtime_error("unable to unwrap content of error result-or");
    return std::get<T>(data);
  }

  const Err& unwrap_err() const {
    if (!data_is_err)
      throw std::runtime_error("unable to unwrap error of ok result-or");
    return std::get<Err>(data);
  }
};
}
