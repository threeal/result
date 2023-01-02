#pragma once

#include <sstream>
#include <string>

namespace res {

struct ErrStream : public std::stringstream {};

struct Err : public std::string {
  Err(const std::string& err_msg) : std::string(err_msg) {}
  Err(const char* err_msg) : std::string(err_msg) {}
  Err(const ErrStream& err_stream) : std::string(err_stream.str()) {}
};
}  // namespace res
