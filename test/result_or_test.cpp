#include <result/result_or.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("check ok result-or") {
  const res::ResultOr<int> res = 32;
  REQUIRE(res.is_ok());
  REQUIRE_FALSE(res.is_err());
}

TEST_CASE("check error result-or") {
  const res::ResultOr<int> res = res::Err("unknown error");
  REQUIRE(res.is_err());
  REQUIRE_FALSE(res.is_ok());
}

TEST_CASE("uninitialized result-or contains error") {
  const res::ResultOr<int> res;
  REQUIRE(res.is_err());
}
