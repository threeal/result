#pragma once

namespace res {

/** A type that represents an ok status (success). */
struct Ok {
  /** Construct a new ok data.
   *
   * @code{.cpp}
   * res::Result result = res::Ok();
   * assert(result.is_ok());
   * @endcode
   */
  Ok() {}
};

}  // namespace res
