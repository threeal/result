#include <result/result.hpp>
#include <catch2/catch_test_macros.hpp>
#include <string>

TEST_CASE("ok test") {
  res::Result<std::string> res = res::ok;
  REQUIRE(res.is_ok());
  REQUIRE_FALSE(res.is_err());
}

TEST_CASE("err test") {
  res::Result<std::string> res = std::string("unknown error");
  REQUIRE(res.is_err());
  REQUIRE_FALSE(res.is_ok());
}
