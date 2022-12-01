#include <result/result.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("check ok result") {
  const res::Result res = res::ok;
  REQUIRE(res.is_ok());
  REQUIRE_FALSE(res.is_err());
}

TEST_CASE("check error result") {
  const res::Result res = "unknown error";
  REQUIRE(res.is_err());
  REQUIRE_FALSE(res.is_ok());
}

TEST_CASE("call `unwrap_err` on error result") {
  const res::internal::ErrMsg err_msg = "unknown error";
  res::Result res = err_msg;
  REQUIRE(res.is_err());
  REQUIRE(res.unwrap_err() == err_msg);
}

TEST_CASE("call `unwrap_err` on ok result") {
  res::Result res = res::ok;
  REQUIRE(res.is_ok());
  REQUIRE_THROWS(res.unwrap_err());
}
