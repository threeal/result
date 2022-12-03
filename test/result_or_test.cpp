#include <result/result_or.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("uninitialized result-or contains error") {
  const res::ResultOr<int> res;
  REQUIRE(res.is_err());
}
