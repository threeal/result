#include <catch2/catch_test_macros.hpp>
#include <result/result.hpp>
#include <string>

TEST_CASE("check ok result") {
  const res::Result res = res::Ok();
  REQUIRE(res.is_ok());
  REQUIRE_FALSE(res.is_err());
}

TEST_CASE("check error result") {
  res::Result res;
  SECTION("from string") { res = res::Err("unknown error"); }
  SECTION("from stream") { res = res::ErrStream() << "unknown error: " << 500; }
  REQUIRE(res.is_err());
  REQUIRE_FALSE(res.is_ok());
}

TEST_CASE("uninitialized result contains error") {
  const res::Result res;
  REQUIRE(res.is_err());
}

TEST_CASE("call `unwrap_err` on error result") {
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

TEST_CASE("call `unwrap_err` on ok result") {
  const res::Result res = res::Ok();
  REQUIRE(res.is_ok());
  REQUIRE_THROWS(res.unwrap_err());
}

TEST_CASE("check rewriting result") {
  res::Result res = res::Ok();
  REQUIRE(res.is_ok());
  std::string err_msg = "unknown error";
  res = res::Err(err_msg);
  REQUIRE(res.is_err());
  REQUIRE(res.unwrap_err() == err_msg);
  err_msg = "other error";
  res = res::Err(err_msg);
  REQUIRE(res.is_err());
  REQUIRE(res.unwrap_err() == err_msg);
  res = res::Ok();
  REQUIRE(res.is_ok());
}

namespace {
res::Result foo(bool is_ok) {
  if (is_ok) return res::Ok();
  return res::Err("unknown error");
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
  const std::string err_msg = "unknown error";
  res::Result res;
  {
    res = res::Err(err_msg);
    REQUIRE(res.is_err());
    REQUIRE(res.unwrap_err() == err_msg);
  }
  REQUIRE(res.is_err());
  REQUIRE(res.unwrap_err() == err_msg);
}
