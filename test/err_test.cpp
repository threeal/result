#include <catch2/catch_test_macros.hpp>
#include <result/result_of.hpp>

TEST_CASE("create error") {
  SECTION("from string") {
    std::string err_msg("unknown error");
    res::Err err(err_msg);
    REQUIRE(err == err_msg);
  }
  SECTION("from c string") {
    res::Err err("unknown error");
    REQUIRE(err == std::string("unknown error"));
  }
}
