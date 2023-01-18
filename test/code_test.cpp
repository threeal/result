#include <catch2/catch_test_macros.hpp>
#include <result/ok.hpp>
#include <result/result.hpp>

#undef assert
#define assert REQUIRE

TEST_CASE("test code snippet") {
  SECTION("Ok::Ok()") {
    res::Result result = res::Ok();
    assert(result.is_ok());
  }
}
