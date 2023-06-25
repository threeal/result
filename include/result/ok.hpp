#pragma once

namespace result {

/** A type that represents an ok status (success).
 * Use this type on res::Result<> to set the status of that data to be ok.
 *
 * @code
 * result::Result<> res = result::Ok();
 * assert(res.is_ok());
 * @endcode
 */
struct Ok {};

}  // namespace result
