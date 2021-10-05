#include <aspartamev0/opt.h>
#include <catch2/catch_test_macros.hpp>

#include <stdexcept>

int add1(int v) {
  return v+1;
}

SCENARIO("Number Opts", "[optnum]") {

  GIVEN("Individual options") {
    aspartamev0::OptInt i {30};
    aspartamev0::OptFloat f {0.25};
    aspartamev0::OptBool b {false};

    THEN("They should have that default value") {
      REQUIRE(i == 30);
      REQUIRE(f == 0.25);
      REQUIRE(!b);
    }

    THEN("We can get the value through the explicit operator") {
      REQUIRE(i() == 30);
      REQUIRE(f() == 0.25);
      REQUIRE(!b());
    }

    THEN("They can be used in function calls") {
      REQUIRE(add1(i) == 31);
    }

    THEN("They can be used in arithmetics") {
      REQUIRE(i + i*2 == 90);
      REQUIRE(i + 4*f == 31);
    }

    THEN("They should have some other value after setting it") {
      i = 50;
      REQUIRE(i == 50);
      f = 0.5;
      REQUIRE(f == 0.5);
      b = true;
      REQUIRE(b);
    }

    THEN("They should have the default value after reset") {
      i = 50;
      i.reset();
      REQUIRE(i == 30);
      f = 0.99;
      f.reset();
      REQUIRE(f == 0.25);
      b = true;
      b.reset();
      REQUIRE(!b);
    }
  }

  GIVEN("Some same-type options") {
    aspartamev0::OptInt i1 {10};
    aspartamev0::OptInt i2 {20};
    aspartamev0::OptInt i2a {i2};

    THEN("Assign one to another shouldn't affect the default value") {
      i1 = i2;
      REQUIRE(i1.getDefault() == 10);
      REQUIRE(i1 == 20);
      i1.reset();
      REQUIRE(i1 == 10);
    }

    THEN("Copy-constructed option should have same default value") {
      REQUIRE(i2a == 20);
      REQUIRE(i2a.getDefault() == 20);
    }
  }

  GIVEN("Individual options to be set by strings") {
    aspartamev0::OptInt i {30};
    aspartamev0::OptFloat f {0.25};
    aspartamev0::OptBool b {false};

    THEN("They can be set with strings") {
      i.set("75");
      REQUIRE(i == 75);
      f.set("0.5");
      REQUIRE(f == 0.5);
      b.set("true");
      REQUIRE(b);
    }

    THEN("Non-parsable things will throw exceptions or fails silently") {
      REQUIRE_THROWS_AS(i.set("xxxooo"), std::domain_error);
      i.set("oioioi", false);
      REQUIRE(i == 0);
      REQUIRE_THROWS_AS(f.set("xxxooo"), std::domain_error);
      f.set("oioioi", false);
      REQUIRE(f == 0);
      REQUIRE_THROWS_AS(b.set("rrrrrr"), std::domain_error);
      b.set("rrrrrr", false);
      REQUIRE(!b);
    }

    THEN("Nullptr will throw exceptions") {
      REQUIRE_THROWS_AS(i.set(nullptr), std::domain_error);
      REQUIRE_THROWS_AS(f.set(nullptr), std::domain_error);
      REQUIRE_THROWS_AS(b.set(nullptr), std::domain_error);
    }

  }

  GIVEN("Special parsings for integer") {
    aspartamev0::OptInt i {30};
    THEN("All sorts of weird values can be parsed") {
      i.set("      149872");
      REQUIRE(i == 149872);
      i.set("0x6fffff");
      REQUIRE(i == 7340031);
      i.set(" -5578");
      REQUIRE(i == -5578);
      i.set(" \n\r\t-3005ABCDEF");
      REQUIRE(i == -3005);
      i.set("77.981");
      REQUIRE(i == 77);
    }
  }

  GIVEN("Special parsings for boolean") {
    aspartamev0::OptBool b {false};
    THEN("All sorts of weird values can be parsed") {
      b.set("vvv");
      REQUIRE(b);
      b.reset();
      b.set("Yaa");
      REQUIRE(b);
      b.reset();
      b.set("   \n\r\tT");
      REQUIRE(b);
      b.reset();
    }
  }

}

