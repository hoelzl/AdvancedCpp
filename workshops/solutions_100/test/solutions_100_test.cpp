#include "solutions_100.hpp"

#include "catch2/catch_test_macros.hpp"

using namespace sol_100;

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

TEST_CASE("sum_from_to()")
{
    SECTION("Non-empty ranges")
    {
        CHECK(sum_from_to(1, 5) == 15);
        CHECK(sum_from_to(1, 1) == 1);
    }

    SECTION("Empty range") { CHECK_THROWS(sum_from_to(1, 0) == 0); }
}
