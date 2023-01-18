#pragma once

#include <sstream>
#include <string>

namespace res {

struct ErrStream : public std::stringstream {};

/** A type that represents an error status (failure).
 * Use this type on res::Result or res::ResultOf to set the status of those data
 * to be failed.
 *
 * @code
 * res::Result result = res::Err("undefined error");
 * assert(result.is_err());
 * @endcode
 *
 * @code
 * res::ResultOf<int> result_of_int = res::Err("undefined error");
 * assert(result_of_int.is_err());
 * @endcode
 */
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
