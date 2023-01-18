#pragma once

#include <sstream>
#include <string>

namespace res {

struct ErrStream : public std::stringstream {};

/** A type that represents an error status (failure). */
struct Err : public std::string {
  /** Construct a new error data using a C++ string.
   * @param err_msg Error message in C++ string.
   *
   * @code{.cpp}
   * std::string err_msg = "undefined error";
   * res::Result result = res::Err(err_msg);
   * assert(result.is_err());  // OK
   * @endcode
   */
  Err(const std::string& err_msg) : std::string(err_msg) {}

  /** Construct a new error data using a C-style string.
   * @param err_msg Error message in C-style string.
   *
   * @code{.cpp}
   * res::Result result = res::Err("undefined error");
   * assert(result.is_err());  // OK
   * @endcode
   */
  Err(const char* err_msg) : std::string(err_msg) {}

  Err(const ErrStream& err_stream) : std::string(err_stream.str()) {}
};
}  // namespace res
