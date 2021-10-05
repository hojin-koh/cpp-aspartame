#include <aspartamev0/optarr.h>
#include <catch2/catch_test_macros.hpp>

#include <stdexcept>

SCENARIO("Number Array Opts", "[optarrnum]") {

  GIVEN("Empty array options") {
    aspartamev0::OptArrInt ei;
    aspartamev0::OptArrFloat ef;
    aspartamev0::OptArrBool eb;

    THEN("They have correct size") {
      REQUIRE(ei.size() == 0);
      REQUIRE(ef.size() == 0);
      REQUIRE(eb.size() == 0);
    }

    THEN("Accessing them from different directions throws") {
      REQUIRE_THROWS(ei[0]);
      REQUIRE_THROWS(ei[-1]);
      REQUIRE_THROWS(ef[0]);
      REQUIRE_THROWS(ef[-1]);
      REQUIRE_THROWS(eb[0]);
      REQUIRE_THROWS(eb[-1]);
    }
  }

  GIVEN("Individual options") {
    aspartamev0::OptArrInt i {30, 40, 50};
    aspartamev0::OptArrFloat f {0.25, 0.75};
    aspartamev0::OptArrBool b {false, false, true, true};

    THEN("We can get the sizes of these options") {
      REQUIRE(i.size() == 3);
      REQUIRE(f.size() == 2);
      REQUIRE(b.size() == 4);
    }

    THEN("They should have that default value") {
      REQUIRE(i[0] == 30);
      REQUIRE(i[1] == 40);
      REQUIRE(i[2] == 50);
      REQUIRE(f[0] == 0.25);
      REQUIRE(f[1] == 0.75);
      REQUIRE(!b[0]);
      REQUIRE(!b[1]);
      REQUIRE(b[2]);
      REQUIRE(b[3]);
    }

    THEN("They should be accessible through negative index") {
      REQUIRE(i[-3] == 30);
      REQUIRE(i[-2] == 40);
      REQUIRE(i[-1] == 50);
      REQUIRE(f[-2] == 0.25);
      REQUIRE(f[-1] == 0.75);
      REQUIRE(!b[-4]);
      REQUIRE(!b[-3]);
      REQUIRE(b[-2]);
      REQUIRE(b[-1]);
    }

    THEN("Their individual value can be set") {
      i[1] = 27;
      REQUIRE(i[-2] == 27);
      f[1] = 1.25;
      REQUIRE(f[-1] == 1.25);
      b[0] = true;
      REQUIRE(b[-4]);
    }

    THEN("Their contents can be cleared") {
      i.clear();
      REQUIRE(i.size() == 0);
      f.clear();
      REQUIRE(f.size() == 0);
      b.clear();
      REQUIRE(b.size() == 0);
    }

    THEN("They should have the default value after reset") {
      i.clear();
      i.reset();
      REQUIRE(i.size() == 3);
      REQUIRE(i[-1] == 50);
      f.clear();
      f.reset();
      REQUIRE(f.size() == 2);
      REQUIRE(f[-1] == 0.75);
      b.clear();
      b.reset();
      REQUIRE(b.size() == 4);
      REQUIRE(b[-1]);
    }

    THEN("Out-of-bound access should throw") {
      REQUIRE_THROWS(i[5]);
      REQUIRE_THROWS(f[8]);
      REQUIRE_THROWS(b[9]);
      REQUIRE_THROWS(i[5] = 10);
      REQUIRE_THROWS(f[8] = 2.5);
      REQUIRE_THROWS(b[9] = false);
    }
  }

  //GIVEN("Some same-type options") {
  //  aspartamev0::OptInt i1 {10};
  //  aspartamev0::OptInt i2 {20};
  //  aspartamev0::OptInt i2a {i2};

  //  THEN("Assign one to another shouldn't affect the default value") {
  //    i1 = i2;
  //    REQUIRE(i1.getDefault() == 10);
  //    REQUIRE(i1 == 20);
  //    i1.reset();
  //    REQUIRE(i1 == 10);
  //  }

  //  THEN("Copy-constructed option should have same default value") {
  //    REQUIRE(i2a == 20);
  //    REQUIRE(i2a.getDefault() == 20);
  //  }
  //}

  //GIVEN("Individual options to be set by strings") {
  //  aspartamev0::OptInt i {30};
  //  aspartamev0::OptFloat f {0.25};
  //  aspartamev0::OptBool b {false};

  //  THEN("They can be set with strings") {
  //    i.set("75");
  //    REQUIRE(i == 75);
  //    f.set("0.5");
  //    REQUIRE(f == 0.5);
  //    b.set("true");
  //    REQUIRE(b);
  //  }

  //  THEN("Non-parsable things will throw exceptions or fails silently") {
  //    REQUIRE_THROWS_AS(i.set("xxxooo"), std::domain_error);
  //    i.set("oioioi", false);
  //    REQUIRE(i == 0);
  //    REQUIRE_THROWS_AS(f.set("xxxooo"), std::domain_error);
  //    f.set("oioioi", false);
  //    REQUIRE(f == 0);
  //    REQUIRE_THROWS_AS(b.set("rrrrrr"), std::domain_error);
  //    b.set("rrrrrr", false);
  //    REQUIRE(!b);
  //  }

  //  THEN("Nullptr will throw exceptions") {
  //    REQUIRE_THROWS_AS(i.set(nullptr), std::domain_error);
  //    REQUIRE_THROWS_AS(f.set(nullptr), std::domain_error);
  //    REQUIRE_THROWS_AS(b.set(nullptr), std::domain_error);
  //  }

  //}

  //GIVEN("Special parsings for integer") {
  //  aspartamev0::OptInt i {30};
  //  THEN("All sorts of weird values can be parsed") {
  //    i.set("      149872");
  //    REQUIRE(i == 149872);
  //    i.set("0x6fffff");
  //    REQUIRE(i == 7340031);
  //    i.set(" -5578");
  //    REQUIRE(i == -5578);
  //    i.set(" \n\r\t-3005ABCDEF");
  //    REQUIRE(i == -3005);
  //    i.set("77.981");
  //    REQUIRE(i == 77);
  //  }
  //}

  //GIVEN("Special parsings for boolean") {
  //  aspartamev0::OptBool b {false};
  //  THEN("All sorts of weird values can be parsed") {
  //    b.set("vvv");
  //    REQUIRE(b);
  //    b.reset();
  //    b.set("Yaa");
  //    REQUIRE(b);
  //    b.reset();
  //    b.set("   \n\r\tT");
  //    REQUIRE(b);
  //    b.reset();
  //  }
  //}

}

