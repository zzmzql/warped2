#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main()
#include "catch.hpp"

#include <memory>

#include "ObjectState.hpp"

Define_ObjectState_Subclass(test_ObjectState) {
public:
    test_ObjectState(int x): x(x) {}
    int x;
};

TEST_CASE("The State can be derived from", "[ObjectState]") {
    test_ObjectState s1 {1};

    SECTION("subclasses can be cloned") {
        auto ps2 = s1.clone();
        auto s2 = static_cast<test_ObjectState&>(*ps2);
        s2.x = 2;
        REQUIRE(s1.x == 1);
        REQUIRE(s2.x == 2);
    }

    SECTION("subclasses can be cloned from base pointer") {
        warped::ObjectState* ps1 = &s1;
        auto ps2 = ps1->clone();
        auto s2 = static_cast<test_ObjectState&>(*ps2);
        s2.x = 2;
        REQUIRE(s1.x == 1);
        REQUIRE(s2.x == 2);
    }
}