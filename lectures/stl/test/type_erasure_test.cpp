#include "type_erasure.hpp"

#include <catch2/catch_test_macros.hpp>
#include <string>

using namespace std::literals::string_literals;
using stl::BinaryFunction;
using stl::BinaryIntFunction;

int my_int_function(int m, int n) { return m + n + 1; }

std::string my_string_function(const std::string& s1, const std::string& s2)
{
    return s1 + s2;
}

BinaryIntFunction pick_int_function(bool add)
{
    if (add) {
        return BinaryIntFunction{[](int m, int n) { return m + n; }};
    }

    return BinaryIntFunction{[](int m, int n) { return m * n; }};
}

TEST_CASE("BinaryIntFunction")
{
    SECTION("Type erase function pointer.")
    {
        const BinaryIntFunction fun{&my_int_function};
        CHECK(fun(3, 4) == 8);
    }

    SECTION("Type erase lambda.")
    {
        const BinaryIntFunction fun([](int x, int y) { return x * y; });
        CHECK(fun(3, 4) == 12);
    }

    SECTION("Wrapping multiple lambdas works for BinaryIntFunction (1).")
    {
        const auto my_fun{pick_int_function(true)};
        CHECK(my_fun(2, 3) == 5);
    }

    SECTION("Wrapping multiple lambdas works for BinaryIntFunction (2).")
    {
        const auto my_fun{pick_int_function(false)};
        CHECK(my_fun(2, 3) == 6);
    }
}

BinaryFunction<int> pick_int_function_2(bool add)
{
    if (add) {
        return [](int m, int n) { return m + n; };
    }

    return [](int m, int n) { return m * n; };
}

TEST_CASE("BinaryFunction")
{
    SECTION("Type erase function pointer for int.")
    {
        const BinaryFunction<int> fun{&my_int_function};
        CHECK(fun(3, 4) == 8);
    }

    SECTION("Type erase lambda for int.")
    {
        const BinaryFunction<int> fun([](int x, int y) { return x * y; });
        CHECK(fun(3, 4) == 12);
    }

    SECTION("Type erase function pointer for std::string.")
    {
        const BinaryFunction<std::string> fun{&my_string_function};
        CHECK(fun("foo "s, "bar"s) == "foo bar"s);
    }

    SECTION("Type erase lambda for std::string.")
    {
        const BinaryFunction<std::string> fun(
            [](const std::string& s1, const std::string& s2) { return s1 + s2; });
        CHECK(fun("abc"s, "d"s) == "abcd"s);
    }

    SECTION("Providing default arguments works for std::string.")
    {
        const BinaryFunction<std::string> fun
        {
            [](const std::string& s1, const std::string& s2) {
                return "["s + s1 + "|"s + s2 + "]"s;
            }
        };
        CHECK(fun("ab"s, "cd"s) == "[ab|cd]"s);
        CHECK(fun() == "[|]"s);
    }

    SECTION("Wrapping multiple lambdas works for BinaryIntFunction (1).")
    {
        const auto my_fun{pick_int_function_2(true)};
        CHECK(my_fun(2, 3) == 5);
    }

    SECTION("Wrapping multiple lambdas works for BinaryIntFunction (2).")
    {
        const auto my_fun{pick_int_function_2(false)};
        CHECK(my_fun(2, 3) == 6);
    }
}
