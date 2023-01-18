#pragma once

#include <sstream>
#include <string>

namespace res {

struct ErrStream : public std::stringstream {};

/** A type that represents an error status (failure). */
struct Err : public std::string {
  /** Construct new error data using a C++ string.
   * @param err_msg The error message.
   *
   * @code{.cpp}
   * res::Err err = std::string("undefined error");
   * assert(err == "undefined error");
   * @endcode
   */
  Err(const std::string& err_msg) : std::string(err_msg) {}

  /** Construct new error data using a C-style string.
   * @param err_msg The error message.
   *
   * @code{.cpp}
   * res::Err err = "unknown error";
   * assert(err == "unknown error");
   * @endcode
   */
  Err(const char* err_msg) : std::string(err_msg) {}

  /** Construct new error data using an error stream.
   * @param err_stream The error stream.
   *
   * @code{.cpp}
   * res::Err err = res::ErrStream() << "not found " << 404;
   * assert(err == "not found 404");
   * @endcode
   */
  Err(const ErrStream& err_stream) : std::string(err_stream.str()) {}
};
}  // namespace res
