#include <result/result.hpp>
#include <catch2/catch_test_macros.hpp>
#include <string>

TEST_CASE("check ok result") {
  const res::Result res = res::ok;
  REQUIRE(res.is_ok());
  REQUIRE_FALSE(res.is_err());
}

TEST_CASE("check error result") {
  const res::Result res = res::err("unknown error");
  REQUIRE(res.is_err());
  REQUIRE_FALSE(res.is_ok());
}

TEST_CASE("uninitialized result contains error") {
  const res::Result res;
  REQUIRE(res.is_err());
}

TEST_CASE("call `unwrap_err` on error result") {
  const std::string err_msg = "unknown error";
  const res::Result res = res::err(err_msg);
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
  std::string err_msg = "unknown error";
  res = res::err(err_msg);
  REQUIRE(res.is_err());
  REQUIRE(res.unwrap_err() == err_msg);
  err_msg = "other error";
  res = res::err(err_msg);
  REQUIRE(res.is_err());
  REQUIRE(res.unwrap_err() == err_msg);
  res = res::ok;
  REQUIRE(res.is_ok());
}

namespace {
res::Result foo(bool is_ok) {
  if (is_ok) return res::ok;
  return res::err("unknown error");
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
