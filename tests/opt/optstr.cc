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
  }

}

