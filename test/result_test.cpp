#include <catch2/catch_test_macros.hpp>
#include <cmath>
#include <result/result.hpp>

TEST_CASE("Result creation") {
  SECTION("Create empty") {
    const result::Result<> res;
    REQUIRE(res.is_err());
    REQUIRE(res.unwrap_err().message == "the result is uninitialized");
  }

  SECTION("Create with OK value") {
    const result::Result<> res = result::Ok{};
    REQUIRE(res.is_ok());
  }

  SECTION("Create with integer value") {
    const result::Result<int> res = 200;
    REQUIRE(res.is_ok());
    REQUIRE(res.unwrap() == 200);
  }

  SECTION("Create with error") {
    const result::Result<int> res = error::Error("unknown error");
    REQUIRE(res.is_err());
    REQUIRE(res.unwrap_err().message == "unknown error");
  }
}

TEST_CASE("Result data getting") {
  SECTION("from result with value") {
    const result::Result<int> res = 200;

    SECTION("Get value") { REQUIRE(res.unwrap() == 200); }

    SECTION("Get error") { REQUIRE_THROWS_AS(res.unwrap_err(), error::Error); }
  }

  SECTION("From result with error") {
    const result::Result<int> res = error::Error("unknown error");

    SECTION("Get value") { REQUIRE_THROWS_AS(res.unwrap(), error::Error); }

    SECTION("Get error") {
      REQUIRE(res.unwrap_err().message == "unknown error");
    }
  }
}

TEST_CASE("Result rewriting") {
  SECTION("Initialize result with value") {
    result::Result<int> res = 200;
    REQUIRE(res.is_ok());
    REQUIRE(res.unwrap() == 200);

    SECTION("Rewrite with error") {
      res = error::Error("unknown error");
      REQUIRE(res.is_err());
      REQUIRE(res.unwrap_err().message == "unknown error");

      SECTION("Rewrite again with another value") {
        res = 201;
        REQUIRE(res.is_ok());
        REQUIRE(res.unwrap() == 201);
      }
    }
  }

  SECTION("Initialize result with error") {
    result::Result<int> res = error::Error("unknown error");
    REQUIRE(res.is_err());
    REQUIRE(res.unwrap_err().message == "unknown error");

    SECTION("Rewrite with value") {
      res = 200;
      REQUIRE(res.is_ok());
      REQUIRE(res.unwrap() == 200);

      SECTION("Rewrite again with another error") {
        res = error::Error("other error");
        REQUIRE(res.is_err());
        REQUIRE(res.unwrap_err().message == "other error");
      }
    }
  }
}

TEST_CASE("Result from function getting") {
  const auto square_root = [](double value) -> result::Result<double> {
    if (value < 0) return error::Error("value must be positive");
    return std::sqrt(value);
  };

  SECTION("From a function returning a valid result") {
    const auto res = square_root(4);
    REQUIRE(res.is_ok());
    REQUIRE(res.unwrap() == 2);
  }

  SECTION("From a function returning an error result") {
    const auto res = square_root(-1);
    REQUIRE(res.is_err());
    REQUIRE(res.unwrap_err().message == "value must be positive");
  }
}

TEST_CASE("Result casting") {
  SECTION("Cast result with value") {
    result::Result<int> src = -1;
    result::Result<unsigned int> dst;

    SECTION("Using as function") { dst = src.as<unsigned int>(); }

    SECTION("Using cast operator") {
      dst = static_cast<result::Result<unsigned int>>(src);
    }

    REQUIRE(dst.is_ok());
    REQUIRE(dst.unwrap() > 0);
  }

  SECTION("Cast result with error") {
    result::Result<int> src = error::Error("unknown error");
    result::Result<unsigned int> dst;

    SECTION("Using as function") { dst = src.as<unsigned int>(); }

    SECTION("Using cast operator") {
      dst = static_cast<result::Result<unsigned int>>(src);
    }

    REQUIRE(dst.is_err());
    REQUIRE(dst.unwrap_err().message == "unknown error");
  }
}
