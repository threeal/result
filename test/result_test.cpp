#include <result/result.hpp>
#include <catch2/catch_test_macros.hpp>
#include <string>

TEST_CASE("ok test") {
  res::Result res = res::ok;
  REQUIRE(res.is_ok());
  REQUIRE_FALSE(res.is_err());
}

TEST_CASE("err test") {
  res::Result res = std::runtime_error("example");
  REQUIRE(res.is_err());
  REQUIRE_FALSE(res.is_ok());
}
