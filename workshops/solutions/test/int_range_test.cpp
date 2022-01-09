#include "int_range.hpp"
#include <catch2/catch_test_macros.hpp>

using stl::IntRangeV0;
using stl::IntRange;

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


TEST_CASE("IntRange")
{
    SECTION("min < max")
    {
        std::vector<int> result{};
        for (int i : IntRange{10, 14}) {
            result.push_back(i);
        }
        CHECK(result == std::vector<int>{10, 11, 12, 13, 14});
    }

    SECTION("min == max")
    {
        std::vector<int> result{};
        for (int i : IntRange{5, 5}) {
            result.push_back(i);
        }
        CHECK(result == std::vector<int>{5});
    }

    SECTION("min > max")
    {
        CHECK_THROWS(IntRange{5, 4});
    }
}
