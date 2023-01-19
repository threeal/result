#pragma once

namespace res {

/** A type that represents an ok status (success).
 * Use this type on res::Result to set the status of that data to be ok.
 *
 * @code
 * res::Result result = res::Ok();
 * assert(result.is_ok());
 * @endcode
 */
struct Ok {};

}  // namespace res
