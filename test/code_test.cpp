#include <catch2/catch_test_macros.hpp>
#include <result/ok.hpp>
#include <result/result.hpp>
#include <string>

#undef assert
#define assert REQUIRE

TEST_CASE("test code snippet") {
  SECTION("Ok::Ok()") {
    res::Result result = res::Ok();
    assert(result.is_ok());
  }
  SECTION("Err::Err(const std::string&)") {
    std::string err_msg = "undefined error";
    res::Result result = res::Err(err_msg);
    assert(result.is_err());
  }
  SECTION("Err::Err(const char*)") {
    res::Result result = res::Err("undefined error");
    assert(result.is_err());
  }
  SECTION("Err::Err(const ErrStream&)") {
    res::Err err = res::ErrStream() << "not found " << 404;
    assert(err == "not found 404");
  }
}
