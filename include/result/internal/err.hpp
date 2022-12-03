#pragma once

#include <string>

namespace res {

namespace internal {

struct Err : public std::string {
  Err(const std::string& err_msg) : std::string(err_msg) {}
  Err(const char* err_msg) : std::string(err_msg) {}
};

const Err uninitialized_err("result is uninitialized");
}

internal::Err err(const std::string& err_msg) { return internal::Err(err_msg); }
internal::Err err(const char* err_msg) { return internal::Err(err_msg); }
}
