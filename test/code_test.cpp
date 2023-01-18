#include <catch2/catch_test_macros.hpp>
#include <result/ok.hpp>
#include <result/result.hpp>
#include <string>

#undef assert
#define assert REQUIRE

TEST_CASE("test code snippet") {
  SECTION("res::Ok struct") {
    SECTION("Ok() constructor") {
      res::Result result = res::Ok();
      assert(result.is_ok());
    }
  }
  SECTION("res::Err struct") {
    SECTION("Err(const std::string&) constructor") {
      std::string err_msg = "undefined error";
      res::Result result = res::Err(err_msg);
      assert(result.is_err());
    }
    SECTION("Err(const char*) constructor") {
      res::Result result = res::Err("undefined error");
      assert(result.is_err());
    }
    SECTION("Err(const ErrStream&) constructor") {
      res::Err err = res::ErrStream() << "not found " << 404;
      assert(err == "not found 404");
    }
  }
}
