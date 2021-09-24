#include <aspartamev0/opt.h>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
using Catch::Matchers::Equals;

#include <stdexcept>

SCENARIO("String Opts", "[optstr]") {

  GIVEN("Individual option") {
    aspartamev0::OptStr s {"ABC"};

    THEN("It should have that default value") {
      REQUIRE_THAT(s(), Equals("ABC"));
      REQUIRE_THAT(s.getDefault(), Equals("ABC"));
    }

    THEN("It should have some other value after setting it") {
      s = "DEF";
      REQUIRE_THAT(s(), Equals("DEF"));
    }

    THEN("It should have the default value after reset") {
      s = "DEF";
      s.reset();
      REQUIRE_THAT(s(), Equals("ABC"));
    }
  }

  GIVEN("Some same-type options") {
    aspartamev0::OptStr s1 {"10"};
    aspartamev0::OptStr s2 {"20"};
    aspartamev0::OptStr s2a {s2};

    THEN("Assign one to another shouldn't affect the default value") {
      s1 = s2;
      REQUIRE_THAT(s1.getDefault(), Equals("10"));
      REQUIRE_THAT(s1(), Equals("20"));
      s1.reset();
      REQUIRE_THAT(s1(), Equals("10"));
    }

    THEN("Copy-constructed option should have same default value") {
      REQUIRE_THAT(s2a.getDefault(), Equals("20"));
      REQUIRE_THAT(s2a(), Equals("20"));
    }
  }

  GIVEN("The crazy nullptr-mania") {
    aspartamev0::OptStr s {"ABC"};

    THEN("Construct with nullptr will throw STL exceptions") {
      REQUIRE_THROWS(aspartamev0::OptStr(nullptr));
    }
    THEN("Set with nullptr will throw exceptions") {
      REQUIRE_THROWS_AS(s.set(nullptr), std::domain_error);
    }
    THEN("Assign with nullptr will throw exceptions") {
      REQUIRE_THROWS_AS(s = nullptr, std::domain_error);
    }
  }

}

