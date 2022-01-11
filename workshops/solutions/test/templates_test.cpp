#include "templates.hpp"
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

using namespace templates;
using namespace std::string_literals;
using Catch::Approx;

TEST_CASE("sum()")
{
    SECTION("Works for ints") {
        CHECK(sum(1, 2) == 3);
    }

    SECTION("Works for doubles") {
        CHECK(sum(1.0, 2.0) == Approx(3.0));
    }

    SECTION("Works for strings") {
        CHECK(sum("ab"s, "cdef"s) == "abcdef"s);
    }
}

TEST_CASE("TestClass")
{
    CHECK(TestClass{3} + TestClass{5} == TestClass{8});
}

TEST_CASE("sum() with TestClass")
{
    SECTION("Two TestClass instances") {
        CHECK(sum(TestClass{2}, TestClass{8}) == TestClass{10});
    }

    SECTION("TestClass and int") {
        // Never works
        // CHECK(sum(TestClass{1}, 3) == TestClass{4});
        CHECK(sum<TestClass>(TestClass{1}, 3) == TestClass{4});
        // CHECK(sum<int>(TestClass{1}, 3) == 4);
    }
}

TEST_CASE("sum2()")
{
    SECTION("Works for ints") {
        CHECK(sum2(1, 2) == 3);
    }

    SECTION("Works for doubles") {
        CHECK(sum2(1.0, 2.0) == Approx(3.0));
    }

    SECTION("Works for strings") {
        CHECK(sum2("ab"s, "cdef"s) == "abcdef"s);
    }
}

TEST_CASE("sum2() with TestClass")
{
    SECTION("Two TestClass instances") {
        CHECK(sum2(TestClass{2}, TestClass{8}) == TestClass{10});
    }

    SECTION("TestClass and int") {
        CHECK(std::is_same_v<decltype(sum2(TestClass{1}, 3)), TestClass>);
        //CHECK(std::is_same_v<decltype(sum2(2, TestClass{1})), int>);
        CHECK(sum2(TestClass{1}, 3) == TestClass{4});
        // CHECK(sum2(2, TestClass{1}) == 3);
        CHECK(sum2<TestClass>(TestClass{1}, 3) == TestClass{4});
        // CHECK(sum2<int>(TestClass{1}, 3) == 4);
    }
}
