#include <catch2/catch_test_macros.hpp>
#include <result/result.hpp>

TEST_CASE("check ok result") {
  const res::Result<int> res = 32;
  REQUIRE(res.is_ok());
  REQUIRE_FALSE(res.is_err());
}

TEST_CASE("check error result") {
  const res::Result<int> res = error::Error("unknown error");
  REQUIRE(res.is_err());
  REQUIRE_FALSE(res.is_ok());
}

TEST_CASE("uninitialized result contains error") {
  const res::Result<int> res;
  REQUIRE(res.is_err());
}

TEST_CASE("call `unwrap` on ok result") {
  const res::Result<int> res = 32;
  REQUIRE(res.is_ok());
  REQUIRE(res.unwrap() == 32);
}

TEST_CASE("call `unwrap` on error result") {
  const res::Result<int> res = error::Error("unknown error");
  REQUIRE(res.is_err());
  REQUIRE_THROWS_AS(res.unwrap(), error::Error);
}

TEST_CASE("call `unwrap_err` on error result") {
  const res::Result<int> res = error::Error("unknown error");
  REQUIRE(res.is_err());
  REQUIRE(res.unwrap_err().message == "unknown error");
}

TEST_CASE("call `unwrap_err` on ok result") {
  const res::Result<int> res = 32;
  REQUIRE(res.is_ok());
  REQUIRE_THROWS_AS(res.unwrap_err(), error::Error);
}

TEST_CASE("check rewriting result") {
  res::Result<int> res = 32;
  REQUIRE(res.is_ok());
  REQUIRE(res.unwrap() == 32);
  res = error::Error("unknown error");
  REQUIRE(res.is_err());
  REQUIRE(res.unwrap_err().message == "unknown error");
  res = error::Error("other error");
  REQUIRE(res.is_err());
  REQUIRE(res.unwrap_err().message == "other error");
  res = 32;
  REQUIRE(res.is_ok());
  REQUIRE(res.unwrap() == 32);
  res = 16;
  REQUIRE(res.is_ok());
  REQUIRE(res.unwrap() == 16);
}

namespace {
res::Result<int> foo(bool is_ok) {
  if (is_ok) return 32;
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
  res::Result<int> res;
  {
    res = 32;
    REQUIRE(res.is_ok());
    REQUIRE(res.unwrap() == 32);
  }
  REQUIRE(res.is_ok());
  REQUIRE(res.unwrap() == 32);
}

TEST_CASE("check if error result is preserved outside the scope") {
  res::Result<int> res;
  {
    res = error::Error("unknown error");
    REQUIRE(res.is_err());
    REQUIRE(res.unwrap_err().message == "unknown error");
  }
  REQUIRE(res.is_err());
  REQUIRE(res.unwrap_err().message == "unknown error");
}

namespace {
struct Int {
  int data;
  explicit operator int() const { return data; }
};
}  // namespace

TEST_CASE("cast result into other result with different type") {
  res::Result<int> res;
  SECTION("from ok result") {
    res::Result<Int> src = Int{32};
    SECTION("using `as()` function") { res = src.as<int>(); }
    SECTION("using explicit cast") { res = static_cast<res::Result<int>>(src); }
    CHECK(res.is_ok());
    if (res.is_ok()) CHECK(res.unwrap() == src.unwrap().data);
  }
  SECTION("from error result") {
    res::Result<Int> src = error::Error("unknown error");
    SECTION("using `as()` function") { res = src.as<int>(); }
    SECTION("using explicit cast") { res = static_cast<res::Result<int>>(src); }
    CHECK(res.is_err());
    if (res.is_err()) CHECK(res.unwrap_err() == src.unwrap_err());
  }
}
