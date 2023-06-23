#include <catch2/catch_test_macros.hpp>
#include <result/result.hpp>
#include <result/result_of.hpp>

#undef assert
#define assert REQUIRE

TEST_CASE("test code snippet") {
  SECTION("res::Result struct") {
    SECTION("res::Result struct") {
      res::Result result = res::Ok();
      assert(result.is_ok());

      result = error::Error("undefined error");
      assert(result.is_err());
      assert(result.unwrap_err().message == "undefined error");
    }
    SECTION("Result() constructor") {
      res::Result result;
      assert(result.is_err());
    }
    SECTION("Result(const Ok&) constructor") {
      res::Result result = res::Ok();
      assert(result.is_ok());
    }
    SECTION("Result(const error::Error&) constructor") {
      res::Result result = error::Error("undefined error");
      assert(result.is_err());
    }
    SECTION("unwrap_err() function") {
      SECTION("1") {
        res::Result result = error::Error("undefined error");
        assert(result.unwrap_err().message == "undefined error");
      }
      SECTION("2") {
        res::Result result = res::Ok();
        REQUIRE_THROWS_AS(result.unwrap_err(), error::Error);
      }
    }
  }
  SECTION("res::ResultOf struct") {
    SECTION("res::ResultOf struct") {
      res::ResultOf<int> result_of_int = 32;
      assert(result_of_int.is_ok());
      assert(result_of_int.unwrap() == 32);

      result_of_int = error::Error("undefined error");
      assert(result_of_int.is_err());
      assert(result_of_int.unwrap_err().message == "undefined error");
    }
    SECTION("ResultOf() constructor") {
      res::ResultOf<int> result_of_int;
      assert(result_of_int.is_err());
    }
    SECTION("ResultOf(const T&) constructor") {
      res::ResultOf<int> result_of_int = 32;
      assert(result_of_int.is_ok());
    }
    SECTION("ResultOf(const Err&) constructor") {
      res::ResultOf<int> result_of_int = error::Error("undefined error");
      assert(result_of_int.is_err());
    }
    SECTION("operator ResultOf<U>() function") {
      res::ResultOf<int> result_of_int = 32;
      auto result_of_float = static_cast<res::ResultOf<float>>(result_of_int);
      assert(result_of_float.unwrap() == 32);
    }
    SECTION("operator Result() function") {
      res::ResultOf<int> result_of_int = 32;
      res::Result result = result_of_int;
      assert(result.is_ok());
    }
    SECTION("ResultOf<U> as<U>() function") {
      res::ResultOf<int> result_of_int = 32;
      res::ResultOf<float> result_of_float = result_of_int.as<float>();
      assert(result_of_float.unwrap() == 32);
    }
    SECTION("unwrap_err() function") {
      SECTION("1") {
        res::ResultOf<int> result_of_int = 32;
        assert(result_of_int.unwrap() == 32);
      }
      SECTION("2") {
        res::ResultOf<int> result_of_int = error::Error("undefined error");
        REQUIRE_THROWS_AS(result_of_int.unwrap(), error::Error);
      }
    }
    SECTION("unwrap_err() function") {
      SECTION("1") {
        res::ResultOf<int> result_of_int = error::Error("undefined error");
        assert(result_of_int.unwrap_err().message == "undefined error");
      }
      SECTION("2") {
        res::ResultOf<int> result_of_int = 32;
        REQUIRE_THROWS_AS(result_of_int.unwrap_err(), error::Error);
      }
    }
  }
  SECTION("res::Ok struct") {
    res::Result result = res::Ok();
    assert(result.is_ok());
  }
  SECTION("res::Err struct") {
    SECTION("Err(const std::string&) constructor") {
      res::Err err = std::string("undefined error");
      assert(err == "undefined error");
    }
    SECTION("Err(const char*) constructor") {
      res::Err err = "unknown error";
      assert(err == "unknown error");
    }
    SECTION("Err(const ErrStream&) constructor") {
      res::Err err = res::ErrStream() << 404 << " not found";
      assert(err == "404 not found");
    }
  }
}
