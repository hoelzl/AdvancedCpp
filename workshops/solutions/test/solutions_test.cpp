#include "solutions.hpp"

#include "catch2/catch_test_macros.hpp"

using namespace sol;

TEST_CASE("IntRangeV0")
{
    SECTION("min < max")
    {
        std::vector<int> result{};
        for (int i : IntRangeV0{10, 14}) {
            result.push_back(i);
        }
        CHECK(result == std::vector<int>{10, 11, 12, 13, 14});
    }

    SECTION("min == max")
    {
        std::vector<int> result{};
        for (int i : IntRangeV0{5, 5}) {
            result.push_back(i);
        }
        CHECK(result == std::vector<int>{5});
    }

    SECTION("min > max")
    {
        CHECK_THROWS(IntRangeV0{5, 4});
    }
}

TEST_CASE("get_op_impl_1()")
{
    CHECK(get_op_impl_1(Op::add)(2, 3) == 5);
    CHECK(get_op_impl_1(Op::mul)(2, 3) == 6);
}

TEST_CASE("get_op_impl_2()")
{
    CHECK(get_op_impl_2(Op::add)(2, 3) == 5);
    CHECK(get_op_impl_2(Op::mul)(2, 3) == 6);
}

TEST_CASE("get_op_impl_3()")
{
    CHECK(get_op_impl_3(Op::add)(2, 3) == 5);
    CHECK(get_op_impl_3(Op::mul)(2, 3) == 6);
}

TEST_CASE("sum_from_to()")
{
    SECTION("Non-empty ranges")
    {
        CHECK(sum_from_to(1, 5) == 15);
        CHECK(sum_from_to(1, 1) == 1);
    }

    SECTION("Empty range") { CHECK_THROWS(sum_from_to(1, 0) == 0); }
}
