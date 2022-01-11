// ReSharper disable CppClangTidyCppcoreguidelinesAvoidCArrays
#include "function_templates.hpp"

#include <catch2/catch_test_macros.hpp>
#include <string>

using namespace templates;
using namespace std::literals::string_literals;

TEST_CASE("max_v1() with explicit instantiation")
{
    SECTION("Works for ints.")
    {
        // Here max_v1() is explicitly instantiated for int; same as
        // 
        // int max_v1(int lhs, int rhs)
        // {
        //     return rhs < lhs ? lhs : rhs;
        // }
        CHECK(max_v1<int>(3, 7) == 7);
        CHECK(max_v1<int>(8, 2) == 8);
    }

    SECTION("Works for strings.") {
        // Here max_v1() is explicitly instantiated for string
        CHECK(max_v1<std::string>("abc"s, "xyz"s) == "xyz"s);
        CHECK(max_v1<std::string>("foo"s, "barbq"s) == "foo"s);
    }
}

TEST_CASE("max_v1()")
{
    SECTION("Works for ints.")
    {
        // Here max_v1() is instantiated for int; T is deduced to be int
        CHECK(max_v1(3, 7) == 7);
        CHECK(max_v1(8, 2) == 8);
    }

    SECTION("Works for strings.") {
        // Here max_v1() is instantiated for string
        CHECK(max_v1("abc"s, "xyz"s) == "xyz"s);
        CHECK(max_v1("foo"s, "barbq"s) == "foo"s);
    }
}

TEST_CASE("max_v2()")
{
    SECTION("Works for ints.")
    {
        // T is deduced to int (again)
        CHECK(max_v2(3, 7) == 7);
        CHECK(max_v2(8, 2) == 8);
    }

    SECTION("Works for strings.") {
        // T is deduced to be string (again)
        CHECK(max_v2("abc"s, "xyz"s) == "xyz"s);
        CHECK(max_v2("foo"s, "barbq"s) == "foo"s);
    }
}

TEST_CASE("Type inference.")
{
    SECTION("Type deduction errors.") {
        // max_v1(1, 2l);
        // max_v1(static_cast<short>(1), 1);
        // max_v1("foo"s, "barbq");

        // max_v2(1, 2l);
        // max_v2(static_cast<short>(1), 1);
        // max_v2("foo"s, "barbq");
        // max_v2("foo", "barbq");
        // This works:
        int i{1};
        int& ri{i};
        max_v2(ri, i);
        // Type can be specified explicitly
        max_v2<int>(1, 2l);
    }

    SECTION("Deduced types.") {
        // Works, but not as expected...
        max_v1("foo", "barbq");

        int i{1};
        // ReSharper disable once CppLocalVariableMayBeConst
        int& ri{i};
        max_v1(ri, i);
        max_v2(ri, i);
        // Type can be specified explicitly
        max_v2<int>(1, 2l);
    }
    // We could also define a template with multiple type parameters
}

TEST_CASE("max_v3()")
{
    SECTION("Works for ints.")
    {
        // T1 and T2 are both deduced to int
        CHECK(max_v3(3, 7) == 7);
        CHECK(max_v3(8, 2) == 8);
    }

    SECTION("Works for ints and doubles.")
    {
        // T1/T2 are deduced to int/double or double/int
        // Result type is determined by aut0
        CHECK(std::is_same_v<decltype(max_v3(3, 7.0)), double>);
        CHECK(std::is_same_v<decltype(max_v3(3.0, 7)), double>);
        CHECK(max_v3(3, 7.0) == 7.0);
        CHECK(max_v3(3.0, 7) == 7.0);
        CHECK(max_v3(8, 2.0) == 8.0);
        CHECK(max_v3(8.0, 2) == 8.0);
    }

    SECTION("Works for strings.") {
        // T is deduced to be string (again)
        CHECK(max_v3("abc"s, "xyz"s) == "xyz"s);
        CHECK(max_v3("foo"s, "barbq"s) == "foo"s);
    }

    SECTION("Works for mixes of strings and const char*") {
        CHECK(max_v3("abc"s, "xyz") == "xyz"s);
        CHECK(max_v3("foo", "barbq"s) == "foo"s);
    }
}

TEST_CASE("max_v4_bad()")
{
    SECTION("Works for ints?")
    {
        CHECK(max_v4_bad(3, 7) == 7);
        CHECK(max_v4_bad(8, 2) == 8);
    }

    SECTION("Works for ints and doubles?")
    {
        CHECK(std::is_same_v<decltype(max_v4_bad(3, 7.0)), double>);
        CHECK(std::is_same_v<decltype(max_v4_bad(3.0, 7)), double>);
        CHECK(max_v4_bad(3, 7.0) == 7.0);
        CHECK(max_v4_bad(3.0, 7) == 7.0);
    }

    SECTION("Works for strings?") {
        CHECK(std::is_same_v<decltype(max_v4_bad("abc"s, "xyz"s)), std::string&>);
        //CHECK(max_v4_bad("abc"s, "xyz"s) == "xyz"s);
        //CHECK(max_v4_bad("foo"s, "barbq"s) == "foo"s);
    }

    SECTION("Works(?) for const char*?")
    {
        CHECK(std::is_same_v<decltype(max_v4_bad("abc", "xyz")), const char*&>);
        //CHECK(strcmp(max_v4_bad("abc", "xyz"), "xyz") == 0);
        //CHECK(strcmp(max_v4_bad("foo", "barbq"), "foo") == 0);
    }
}

TEST_CASE("max_v4()")
{
    SECTION("Works for ints.")
    {
        CHECK(max_v4(3, 7) == 7);
        CHECK(max_v4(8, 2) == 8);
    }

    SECTION("Works for ints and doubles.")
    {
        CHECK(std::is_same_v<decltype(max_v4(3, 7.0)), double>);
        CHECK(std::is_same_v<decltype(max_v4(3.0, 7)), double>);
        CHECK(max_v4(3, 7.0) == 7.0);
        CHECK(max_v4(3.0, 7) == 7.0);
    }

    SECTION("Works for strings.") {
        CHECK(std::is_same_v<decltype(max_v4("abc"s, "xyz"s)), std::string>);
        CHECK(max_v4("abc"s, "xyz"s) == "xyz"s);
        CHECK(max_v4("foo"s, "barbq"s) == "foo"s);
    }
}

TEST_CASE("std::decay_t()")
{
    CHECK(std::is_same_v<std::decay_t<int>, int>);
    CHECK(std::is_same_v<std::decay_t<const int>, int>);
    CHECK(std::is_same_v<std::decay_t<int&>, int>);
    CHECK(std::is_same_v<std::decay_t<int&&>, int>);
    CHECK(std::is_same_v<std::decay_t<const int&>, int>);
    CHECK(std::is_same_v<std::decay_t<int[42]>, int*>);
    CHECK(std::is_same_v<std::decay_t<int(int)>, int(*)(int)>);
}

TEST_CASE("max_v5()")
{
    SECTION("Works for ints.")
    {
        CHECK(max_v5(3, 7) == 7);
        CHECK(max_v5(8, 2) == 8);
    }

    SECTION("Works for ints and doubles.")
    {
        CHECK(std::is_same_v<decltype(max_v5(3, 7.0)), double>);
        CHECK(std::is_same_v<decltype(max_v5(3.0, 7)), double>);
        CHECK(max_v5(3, 7.0) == 7.0);
        CHECK(max_v5(3.0, 7) == 7.0);
    }

    SECTION("Works for strings.") {
        CHECK(std::is_same_v<decltype(max_v5("abc"s, "xyz"s)), std::string>);
        CHECK(max_v5("abc"s, "xyz"s) == "xyz"s);
        CHECK(max_v5("foo"s, "barbq"s) == "foo"s);
    }
}

TEST_CASE("max_v6()")
{
    SECTION("Works for ints.")
    {
        CHECK(max_v6(3, 7) == 7);
        CHECK(max_v6(8, 2) == 8);
    }

    SECTION("Works for ints and doubles.")
    {
        CHECK(std::is_same_v<decltype(max_v6(3, 7.0)), double>);
        CHECK(std::is_same_v<decltype(max_v6(3.0, 7)), double>);
        CHECK(max_v6(3, 7.0) == 7.0);
        CHECK(max_v6(3.0, 7) == 7.0);
    }

    SECTION("Can specify the return type.")
    {
        CHECK(std::is_same_v<decltype(max_v6<int, int, double>(1, 2)), double>);
        CHECK(max_v6<int, int, double>(1, 2) == 2.0);
    }

    SECTION("Works for strings.") {
        CHECK(std::is_same_v<decltype(max_v6("abc"s, "xyz"s)), std::string>);
        CHECK(max_v6("abc"s, "xyz"s) == "xyz"s);
        CHECK(max_v6("foo"s, "barbq"s) == "foo"s);
    }
}

TEST_CASE("Overloads V1.")
{
    CHECK(overload_v1(1, 2) == non_template_version_called);
    // Force a call to the template version:
    CHECK(overload_v1<>(1, 2) == template_version_called);
    CHECK(overload_v1(1.0, 2.0) == template_version_called);
    CHECK(overload_v1(1.0, 2) == non_template_version_called);
    CHECK(overload_v1('a', 1) == non_template_version_called);
    CHECK(overload_v1('a', 'b') == template_version_called);
}

TEST_CASE("Overloads V2.")
{
    CHECK(overload_v2(1, 2) == non_template_version_called);
    CHECK(overload_v2(1.0, 2.0) == template_version_called);
    CHECK(overload_v2(1.0, 2) == template_version_called);
    CHECK(overload_v2('a', 1) == template_version_called);
    CHECK(overload_v2('a', 'b') == template_version_called);
}

TEST_CASE("max_v7()")
{
    SECTION("Works for ints.")
    {
        CHECK(max_v7(3, 7) == 7);
        CHECK(max_v7(8, 2) == 8);
    }

    SECTION("Works for int*.") {
        int i{2};
        int j{5};
        CHECK(max_v7(&i, &j) == 5);
        CHECK(max_v7(&j, &i) == 5);
    }

    SECTION("Works for const char*.") {
        CHECK(std::is_same_v<decltype(max_v7("abc", "xyz")), const char*>);
        CHECK(std::strcmp(max_v7("abc", "xyz"), "xyz") == 0);
        CHECK(std::strcmp(max_v7("foo", "barbq"), "foo") == 0);
    }

    SECTION("Works for strings.") {
        CHECK(std::is_same_v<decltype(max_v7("abc"s, "xyz"s)), std::string>);
        CHECK(max_v7("abc"s, "xyz"s) == "xyz"s);
        CHECK(max_v7("foo"s, "barbq"s) == "foo");
    }
}
