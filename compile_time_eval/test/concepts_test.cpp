#include "concepts.hpp"

#include <catch2/catch_test_macros.hpp>
#include <cstring>
#include <iostream>

using namespace ct_concepts;

TEST_CASE("max_fun_templ_1()")
{
    SECTION("Integers")
    {
        // Seems to work well...
        CHECK(max_fun_templ_1(10, 20) == 20);
    }

    SECTION("Strings (const char*)")
    {
        // ...but it (a) invokes deprecated behavior, and (b) may or may not return the
        // desired result.

        // OK... (perhaps)
        CHECK(std::strcmp(max_fun_templ_1("foo", "bar"), "foo") == 0);
        // Oops... (perhaps)
        CHECK_FALSE(std::strcmp(max_fun_templ_1("bar", "foo"), "foo") == 0);

        const char* foo{"foo"};
        const char* bar{"bar"};

        // Oops! (Not guaranteed, but likely...)
        CHECK_FALSE(std::strcmp(max_fun_templ_1(foo, bar), foo) == 0);
        CHECK(std::strcmp(max_fun_templ_1(foo, bar), bar) == 0);
    }
}

TEST_CASE("max_fun_templ_2()")
{
    SECTION("Integers") { CHECK(max_fun_templ_2(10, 20) == 20); }

    SECTION("Strings (const char*)")
    {
        // OK (really!)
        CHECK(std::strcmp(max_fun_templ_2("foo", "bar"), "foo") == 0);
        // OK (as well)
        CHECK(std::strcmp(max_fun_templ_2("bar", "foo"), "foo") == 0);

        const char* foo{"foo"};
        const char* bar{"bar"};

        CHECK(std::strcmp(max_fun_templ_2(foo, bar), foo) == 0);
        CHECK_FALSE(std::strcmp(max_fun_templ_2(foo, bar), bar) == 0);
    }

    SECTION("Pointers to int")
    {
        // But we want this to compare the values as well, not the pointers...
        // And similarly for other pointer types...
        int i{2};
        int j{1};
        CHECK(max_fun_templ_2(&i, &j) == &j);
    }
}


TEST_CASE("max_fun_templ_3()")
{
    SECTION("Integers") { CHECK(max_fun_templ_3(10, 20) == 20); }

    SECTION("Strings (const char*)")
    {
        // OK (really!)
        CHECK(std::strcmp(max_fun_templ_3("foo", "bar"), "foo") == 0);
        // OK (as well)
        CHECK(std::strcmp(max_fun_templ_3("bar", "foo"), "foo") == 0);

        const char* foo{"foo"};
        const char* bar{"bar"};

        CHECK(std::strcmp(max_fun_templ_3(foo, bar), foo) == 0);
        CHECK_FALSE(std::strcmp(max_fun_templ_3(foo, bar), bar) == 0);
    }

    SECTION("Pointers to int")
    {
        // But we want this to compare the values as well, not the pointers...
        // And similarly for other pointer types...
        int i{2};
        int j{1};
        CHECK(max_fun_templ_3(&i, &j) == 2);
    }

    SECTION("Smart Pointers")
    {
        // But what about smart pointers?
        [[maybe_unused]] auto pi{std::make_unique<int>(2)};
        [[maybe_unused]] auto pj{std::make_unique<int>(1)};
        // CHECK(max_fun_templ_2(pi, pj));
    }
}
