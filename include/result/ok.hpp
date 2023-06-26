#pragma once

namespace result {

/**
 * @brief Represents a successful (OK) status.
 *
 * The `Ok` struct is used in conjunction with `result::Result` to indicate a
 * successful status. It serves as a marker type to set the status of the result
 * to OK when no specific value is needed.
 *
 * @code{.cpp}
 * result::Result<> res = result::Ok{};
 * assert(res.is_ok());
 * @endcode
 */
struct Ok {};

}  // namespace result
