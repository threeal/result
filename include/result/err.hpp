#pragma once

#include <string>

namespace res {

struct Err : public std::string {
  Err(const std::string& err_msg) : std::string(err_msg) {}
  Err(const char* err_msg) : std::string(err_msg) {}
};
}  // namespace res
