#include <catch2/catch_test_macros.hpp>
#include <result/result.hpp>

#undef assert
#define assert REQUIRE

TEST_CASE("test code snippet") {
  SECTION("res::Result struct") {
    SECTION("res::Result struct") {
      res::Result<int> result_of_int = 32;
      assert(result_of_int.is_ok());
      assert(result_of_int.unwrap() == 32);

      result_of_int = error::Error("undefined error");
      assert(result_of_int.is_err());
      assert(result_of_int.unwrap_err().message == "undefined error");
    }
    SECTION("Result() constructor") {
      res::Result<int> result_of_int;
      assert(result_of_int.is_err());
    }
    SECTION("Result(const T&) constructor") {
      res::Result<int> result_of_int = 32;
      assert(result_of_int.is_ok());
    }
    SECTION("Result(const Err&) constructor") {
      res::Result<int> result_of_int = error::Error("undefined error");
      assert(result_of_int.is_err());
    }
    SECTION("operator Result<U>() function") {
      res::Result<int> result_of_int = 32;
      auto result_of_float = static_cast<res::Result<float>>(result_of_int);
      assert(result_of_float.unwrap() == 32);
    }
    SECTION("Result<U> as<U>() function") {
      res::Result<int> result_of_int = 32;
      res::Result<float> result_of_float = result_of_int.as<float>();
      assert(result_of_float.unwrap() == 32);
    }
    SECTION("unwrap_err() function") {
      SECTION("1") {
        res::Result<int> result_of_int = 32;
        assert(result_of_int.unwrap() == 32);
      }
      SECTION("2") {
        res::Result<int> result_of_int = error::Error("undefined error");
        REQUIRE_THROWS_AS(result_of_int.unwrap(), error::Error);
      }
    }
    SECTION("unwrap_err() function") {
      SECTION("1") {
        res::Result<int> result_of_int = error::Error("undefined error");
        assert(result_of_int.unwrap_err().message == "undefined error");
      }
      SECTION("2") {
        res::Result<int> result_of_int = 32;
        REQUIRE_THROWS_AS(result_of_int.unwrap_err(), error::Error);
      }
    }
  }
  SECTION("res::Ok struct") {
    res::Result<> result = res::Ok();
    assert(result.is_ok());
  }
}
