#include "hidden_friends.hpp"

#include "catch2/catch_test_macros.hpp"

using namespace ops;

TEST_CASE("CompareMeHiddenFriends") 
{
    CompareMeHiddenFriends cm20{20};
    CompareMeHiddenFriends cm20_a{20};
    CompareMeHiddenFriends cm32{32};
    CompareMeHiddenFriends cm120{120};

    SECTION("Construction from char const*")
    {
        CompareMeHiddenFriends cm{"123"};
        CHECK(cm.id == 123);
    }

    SECTION("Equality")
    {
        CHECK(cm20 == cm20);
        CHECK(cm20 == cm20_a);
        CHECK(cm20 != cm32);
        CHECK(cm20 == cm120);
    }

    SECTION("Comparison")
    {
        CHECK_FALSE(cm20 < cm20_a);
        CHECK(cm20 <= cm20_a);
        CHECK_FALSE(cm20_a > cm20);
        CHECK(cm20_a >= cm20);

        CHECK(cm20 < cm32);
        CHECK(cm20 <= cm32);
        CHECK(cm32 > cm20);
        CHECK(cm32 >= cm20);

        CHECK_FALSE(cm20 < cm120);
        CHECK_FALSE(cm120 > cm20);
    }

    SECTION("Comparison with ints")
    {
        CHECK_FALSE(cm20 < 20);
        CHECK(cm20 <= 20);
        CHECK_FALSE(20 > cm20);
        CHECK(20 >= cm20);
    }

    SECTION("Comparison with strings")
    {
        std::string s20{"20"};
        CHECK_FALSE(cm20 < s20);
        CHECK(cm20 <= s20);
        CHECK_FALSE(s20 > cm20);
        CHECK(s20 >= cm20);
    }

    SECTION("Integer/String Comparison")
    {
        // Compile error (as it should be)!
        // CHECK(10 == std::string{"10"});
    }
}
