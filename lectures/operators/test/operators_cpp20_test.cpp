#include "operators_cpp20.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace ops20;

TEST_CASE("EqMe")
{
    EqMe em1{1};
    EqMe em1_a{1};
    EqMe em2{2};
    EqMe em101{101};
    
    SECTION("Equality and inequality")
    {
        CHECK(em1 == em1);
        CHECK(em1 == em1_a);
        CHECK(em1 != em2);
        CHECK(em1 == em101);
    }
    
    SECTION("Equality with ints")
    {
        CHECK(em1 == 1);
        CHECK_FALSE(em1 == 2);
        CHECK(1 == em1);
        CHECK_FALSE(2 == em1);
    }

    SECTION("Equality with strings") {
        CHECK(em1 == std::string{"1"});
        CHECK(std::string{"1"} == em1);

        CHECK(em1 == "1");
        CHECK("1" == em1);

        CHECK(em1 == "101");
        CHECK("101" == em1);
    }
 
    SECTION("Inequality with strings") {
        CHECK(em1 != std::string{"2"});
        CHECK(std::string{"2"} != em1);

        CHECK(em1 != "2");
        CHECK("2" != em1);
    }

    SECTION("Equality between ints and strings") {
        // Compile error:
        // CHECK(1 == std::string{"1"});
    }
}

TEST_CASE("OpSpaceship") 
{
    OpSpaceship os20{20};
    OpSpaceship os20_0{20, 0};
    OpSpaceship os20_1{20, 1};
    OpSpaceship os32{32};

    SECTION("Equality and inequality")
    {
        CHECK(os20 == os20);
        CHECK(os20 == os20_0);
        CHECK(os20 != os20_1);
        CHECK(os20 != os32);
    }

    SECTION("Comparison")
    {
        CHECK_FALSE(os20 < os20_0);
        CHECK_FALSE(os20_0 < os20);

        CHECK(os20 < os20_1);
        CHECK_FALSE(os20_1 < os20);

        CHECK(os20 <= os20_0);
        CHECK(os20 <= os20_1);

        CHECK_FALSE(os20_0 > os20);
        CHECK_FALSE(os20_0 > os20_1);
        CHECK(os20_0 >= os20);

        CHECK(os20 < os32);
        CHECK(os20 <= os32);
        CHECK_FALSE(os32 < os20);
        CHECK_FALSE(os32 <= os20);

        CHECK(os32 > os20);
        CHECK(os32 >= os20);
        CHECK_FALSE(os20 > os32);
        CHECK_FALSE(os20 >= os32);
    }
}

TEST_CASE("CompareMeCpp20") 
{
    CompareMe cm20{20};
    CompareMe cm20_a{20};
    CompareMe cm32{32};
    CompareMe cm120{120};
    
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
}
