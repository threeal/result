#include <catch2/catch_test_macros.hpp>
#include <result/result_of.hpp>

TEST_CASE("check ok result-of") {
  const res::ResultOf<int> res = 32;
  REQUIRE(res.is_ok());
  REQUIRE_FALSE(res.is_err());
}

TEST_CASE("check error result-of") {
  res::ResultOf<int> res;
  SECTION("from string") { res = res::Err("unknown error"); }
  SECTION("from stream") { res = res::ErrStream() << "unknown error: " << 500; }
  REQUIRE(res.is_err());
  REQUIRE_FALSE(res.is_ok());
}

TEST_CASE("uninitialized result-of contains error") {
  const res::ResultOf<int> res;
  REQUIRE(res.is_err());
}

TEST_CASE("call `unwrap` on ok result-of") {
  const res::ResultOf<int> res = 32;
  REQUIRE(res.is_ok());
  REQUIRE(res.unwrap() == 32);
}

TEST_CASE("call `unwrap` on error result-of") {
  const res::ResultOf<int> res = res::Err("unknown error");
  REQUIRE(res.is_err());
  REQUIRE_THROWS_AS(res.unwrap(), error::Error);
}

TEST_CASE("call `unwrap_err` on error result-of") {
  res::Result res;
  std::string err_msg;
  SECTION("from string") {
    res = res::Err("unknown error");
    err_msg = "unknown error";
  }
  SECTION("from stream") {
    res = res::ErrStream() << "unknown error: " << 500;
    err_msg = "unknown error: 500";
  }
  REQUIRE(res.is_err());
  REQUIRE(res.unwrap_err() == err_msg);
}

TEST_CASE("call `unwrap_err` on ok result-of") {
  const res::ResultOf<int> res = 32;
  REQUIRE(res.is_ok());
  REQUIRE_THROWS_AS(res.unwrap_err(), error::Error);
}

TEST_CASE("check rewriting result-of") {
  res::ResultOf<int> res = 32;
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

namespace {
res::ResultOf<int> foo(bool is_ok) {
  if (is_ok) return 32;
  return res::Err("unknown error");
}
}  // namespace

TEST_CASE("get result-of from function returning ok") {
  const auto res = foo(true);
  REQUIRE(res.is_ok());
}

TEST_CASE("get result-of from function returning error") {
  const auto res = foo(false);
  REQUIRE(res.is_err());
}

TEST_CASE("check if ok result-of is preserved outside the scope") {
  res::ResultOf<int> res;
  {
    res = 32;
    REQUIRE(res.is_ok());
    REQUIRE(res.unwrap() == 32);
  }
  REQUIRE(res.is_ok());
  REQUIRE(res.unwrap() == 32);
}

TEST_CASE("check if error result-of is preserved outside the scope") {
  res::ResultOf<int> res;
  {
    res = res::Err("unknown error");
    REQUIRE(res.is_err());
    REQUIRE(res.unwrap_err() == std::string("unknown error"));
  }
  REQUIRE(res.is_err());
  REQUIRE(res.unwrap_err() == std::string("unknown error"));
}

TEST_CASE("cast result-of into result") {
  res::ResultOf<int> src;
  SECTION("from ok result-of") {
    res::Result res = src = 32;
    CHECK(res.is_ok());
  }
  SECTION("from error result-of") {
    res::Result res = src = res::Err("unknown error");
    CHECK(res.is_err());
    if (res.is_err()) CHECK(res.unwrap_err() == src.unwrap_err());
  }
}

namespace {
struct Int {
  int data;
  explicit operator int() const { return data; }
};
}  // namespace

TEST_CASE("cast result-of into other result-of with different type") {
  res::ResultOf<int> res;
  SECTION("from ok result-of") {
    res::ResultOf<Int> src = Int{32};
    SECTION("using `as()` function") { res = src.as<int>(); }
    SECTION("using explicit cast") {
      res = static_cast<res::ResultOf<int>>(src);
    }
    CHECK(res.is_ok());
    if (res.is_ok()) CHECK(res.unwrap() == src.unwrap().data);
  }
  SECTION("from error result-of") {
    res::ResultOf<Int> src = res::Err("unknown error");
    SECTION("using `as()` function") { res = src.as<int>(); }
    SECTION("using explicit cast") {
      res = static_cast<res::ResultOf<int>>(src);
    }
    CHECK(res.is_err());
    if (res.is_err()) CHECK(res.unwrap_err() == src.unwrap_err());
  }
}
