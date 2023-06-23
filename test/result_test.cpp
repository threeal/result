#include <catch2/catch_test_macros.hpp>
#include <result/result.hpp>
#include <string>

TEST_CASE("check ok result") {
  const res::Result res = res::Ok();
  REQUIRE(res.is_ok());
  REQUIRE_FALSE(res.is_err());
}

TEST_CASE("check error result") {
  const res::Result res = error::Error("unknown error");
  REQUIRE(res.is_err());
  REQUIRE_FALSE(res.is_ok());
}

TEST_CASE("uninitialized result contains error") {
  const res::Result res;
  REQUIRE(res.is_err());
}

TEST_CASE("call `unwrap_err` on error result") {
  const res::Result res = error::Error("unknown error");
  REQUIRE(res.is_err());
  REQUIRE(res.unwrap_err().message == "unknown error");
}

TEST_CASE("call `unwrap_err` on ok result") {
  const res::Result res = res::Ok();
  REQUIRE(res.is_ok());
  REQUIRE_THROWS_AS(res.unwrap_err(), error::Error);
}

TEST_CASE("check rewriting result") {
  res::Result res = res::Ok();
  REQUIRE(res.is_ok());
  res = error::Error("unknown error");
  REQUIRE(res.is_err());
  REQUIRE(res.unwrap_err().message == "unknown error");
  res = error::Error("other error");
  REQUIRE(res.is_err());
  REQUIRE(res.unwrap_err().message == "other error");
  res = res::Ok();
  REQUIRE(res.is_ok());
}

namespace {
res::Result foo(bool is_ok) {
  if (is_ok) return res::Ok();
  return error::Error("unknown error");
}
}  // namespace

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
    res = res::Ok();
    REQUIRE(res.is_ok());
  }
  REQUIRE(res.is_ok());
}

TEST_CASE("check if error result is preserved outside the scope") {
  res::Result res;
  {
    res = error::Error("unknown error");
    REQUIRE(res.is_err());
    REQUIRE(res.unwrap_err().message == "unknown error");
  }
  REQUIRE(res.is_err());
  REQUIRE(res.unwrap_err().message == "unknown error");
}
