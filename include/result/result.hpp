#pragma once

#include <error/error.hpp>
#include <optional>

#include "ok.hpp"
#include "result_of.hpp"

namespace res {

/**
 * @brief Alias type for returning and propagating an error.
 *
 * This type can have an OK status (success) which does not contain an error, or
 * an error status (failure) which contains an error.
 * Use res::ResultOf if the type needs to contain a value when the status is OK.
 *
 * @code
 * res::Result result = res::Ok();
 * assert(result.is_ok());
 *
 * result = error::Error("undefined error");
 * assert(result.is_err());
 * assert(result.unwrap_err().message == "undefined error");
 * @endcode
 */
using Result = ResultOf<Ok>;

}  // namespace res
