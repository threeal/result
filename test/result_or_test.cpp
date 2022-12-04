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

TEST_CASE("call `unwrap` on ok result-or") {
  const res::ResultOr<int> res = 32;
  REQUIRE(res.is_ok());
  REQUIRE(res.unwrap() == 32);
}

TEST_CASE("call `unwrap` on error result-or") {
  const res::ResultOr<int> res = res::Err("unknown error");
  REQUIRE(res.is_err());
  REQUIRE_THROWS(res.unwrap());
}

TEST_CASE("call `unwrap_err` on error result-or") {
  const std::string err_msg = "unknown error";
  const res::ResultOr<int> res = res::Err(err_msg);
  REQUIRE(res.is_err());
  REQUIRE(res.unwrap_err() == err_msg);
}

TEST_CASE("call `unwrap_err` on ok result-or") {
  const res::ResultOr<int> res = 32;
  REQUIRE(res.is_ok());
  REQUIRE_THROWS(res.unwrap_err());
}

TEST_CASE("check rewriting result-or") {
  res::ResultOr<int> res = 32;
  REQUIRE(res.is_ok());
  REQUIRE(res.unwrap() == 32);
  std::string err_msg = "unknown error";
  res = res::Err(err_msg);
  REQUIRE(res.is_err());
  REQUIRE(res.unwrap_err() == err_msg);
  err_msg = "other error";
  res = res::Err(err_msg);
  REQUIRE(res.is_err());
  REQUIRE(res.unwrap_err() == err_msg);
  res = 32;
  REQUIRE(res.is_ok());
  REQUIRE(res.unwrap() == 32);
  res = 16;
  REQUIRE(res.is_ok());
  REQUIRE(res.unwrap() == 16);
}
