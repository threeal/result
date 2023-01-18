#include <catch2/catch_test_macros.hpp>
#include <result/ok.hpp>
#include <result/result.hpp>
#include <result/result_of.hpp>
#include <string>

#undef assert
#define assert REQUIRE

TEST_CASE("test code snippet") {
  SECTION("res::Ok struct") {
    res::Result result = res::Ok();
    assert(result.is_ok());
  }
  SECTION("res::Err struct") {
    SECTION("res::Err struct") {
      res::Result result = res::Err("undefined error");
      assert(result.is_err());
      res::ResultOf<int> result_of_int = res::Err("undefined error");
      assert(result_of_int.is_err());
    }
    SECTION("Err(const std::string&) constructor") {
      res::Err err = std::string("undefined error");
      assert(err == "undefined error");
    }
    SECTION("Err(const char*) constructor") {
      res::Err err = "unknown error";
      assert(err == "unknown error");
    }
    SECTION("Err(const ErrStream&) constructor") {
      res::Err err = res::ErrStream() << "not found " << 404;
      assert(err == "not found 404");
    }
  }
}
