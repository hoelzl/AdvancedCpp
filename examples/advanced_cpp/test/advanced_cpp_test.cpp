// ReSharper disable CppClangTidyConcurrencyMtUnsafe
// ReSharper disable CppClangTidyClangDiagnosticDeprecatedDeclarations
#include "advanced_cpp.hpp"

#include <cstdlib>

#include "catch2/catch_test_macros.hpp"

using advanced_cpp::compute_sum;
using advanced_cpp::pessimistic_estimate;
using advanced_cpp::throw_an_exception;

TEST_CASE("compute_sum()")
{
    SECTION("Works for positive numbers") { CHECK(compute_sum(1, 2) == 3); }

    SECTION("Works, given the environment is sane")
    {
        // Imagine something more useful is required here...
        REQUIRE(std::getenv("path") != nullptr);
        // OK, it makes sense to execute the real test cases:
        CHECK(compute_sum(2, 2) == 4);
    }
}

TEST_CASE("Failing tests", "[.][failing]")
{
    SECTION("Failing requirement")
    {
        // Are we doing binary arithmetic?
        REQUIRE(compute_sum(1, 1) == 10);
        // Then this makes sense.
        CHECK(compute_sum(10, 10) == 100);
    }

    SECTION("Failing check")
    {
        CHECK(compute_sum(1, 1) == 3);
        CHECK(compute_sum(10, 10) == 20);
    }
}

TEST_CASE("pessimistic_estimate()")
{
    SECTION("Is not optimistic") { CHECK_FALSE(pessimistic_estimate()); }

    SECTION("Does not throw, either") { CHECK_NOTHROW(pessimistic_estimate()); }
}

TEST_CASE("throw_an_exception()")
{
    SECTION("Throws an exception") { CHECK_THROWS(throw_an_exception()); }

    SECTION("Throws an exception of type std::invalid_argument")
    {
        CHECK_THROWS_AS(throw_an_exception(), std::invalid_argument);
    }
}