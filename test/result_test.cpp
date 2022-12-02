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

TEST_CASE("uninitialized result contains error") {
  const res::Result res;
  REQUIRE(res.is_err());
}

TEST_CASE("call `unwrap_err` on error result") {
  const res::internal::ErrMsg err_msg = "unknown error";
  const res::Result res = err_msg;
  REQUIRE(res.is_err());
  REQUIRE(res.unwrap_err() == err_msg);
}

TEST_CASE("call `unwrap_err` on ok result") {
  const res::Result res = res::ok;
  REQUIRE(res.is_ok());
  REQUIRE_THROWS(res.unwrap_err());
}

TEST_CASE("check rewriting result") {
  res::Result res = res::ok;
  REQUIRE(res.is_ok());
  res::internal::ErrMsg err_msg = "unknown error";
  res = err_msg;
  REQUIRE(res.is_err());
  REQUIRE(res.unwrap_err() == err_msg);
  res = err_msg = "other error";
  REQUIRE(res.is_err());
  REQUIRE(res.unwrap_err() == err_msg);
  res = res::ok;
  REQUIRE(res.is_ok());
}

namespace {
res::Result foo(bool is_ok) {
  if (is_ok) return res::ok;
  return "unknown error";
}
}

TEST_CASE("get result from function returning ok") {
  const auto res = foo(true);
  REQUIRE(res.is_ok());
}

TEST_CASE("get result from function returning error") {
  const auto res = foo(false);
  REQUIRE(res.is_err());
}

TEST_CASE("check if ok result is preserved outside the scope") {
  res::Result res;
  {
    res = foo(true);
    REQUIRE(res.is_ok());
  }
  REQUIRE(res.is_ok());
}

TEST_CASE("check if error result is preserved outside the scope") {
  res::Result res;
  {
    res = foo(false);
    REQUIRE(res.is_err());
  }
  REQUIRE(res.is_err());
}
