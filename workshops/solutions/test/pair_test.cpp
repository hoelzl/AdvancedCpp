#include "pair.hpp"

#include <catch2/catch_test_macros.hpp>
#include <string>

using namespace template_pair;
using namespace std::string_literals;

TEST_CASE("Pair<T1, T2>")
{
    SECTION("Can store and retrieve two different types")
    {
        Pair p{123, "foo"s};
        CHECK(p.first() == 123);
        CHECK(p.second() == "foo"s);
    }
}

TEST_CASE("Pair<T1, unsigned short>")
{
    SECTION("Can store and retrieve values")
    {
        Pair p{246, static_cast<unsigned short>(123)};
        CHECK(p.first() == 246);
        CHECK(p.second() == 123u);
    }
}

TEST_CASE("Pair<unsigned short, T2>")
{
    SECTION("Can store and retrieve values")
    {
        Pair p{static_cast<unsigned short>(123), 246};
        CHECK(p.first() == 123u);
        CHECK(p.second() == 246);
    }
}

TEST_CASE("Pair<unsigned short, unsigned short>")
{
    SECTION("Can store and retrieve values")
    {
        Pair p{static_cast<unsigned short>(123), static_cast<unsigned short>(246)};
        CHECK(p.first() == 123u);
        CHECK(p.second() == 246u);
    }
}
