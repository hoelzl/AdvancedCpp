#include "throw_only.hpp"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

using namespace throw_only;
using Catch::Approx;

TEST_CASE("ThrowOnly, ComputeSum_ComputesSumOfArguments")
{
    const auto result{compute_sum(2.0, 5.0)};
    CHECK(result == Approx(7.0));
}


TEST_CASE("ThrowOnly, ComputeSqrt_Computesresult_WhenCalledWithZeroArg")
{
    const auto result{compute_sqrt(0.0)};
    CHECK(result == Approx(0.0));
}


TEST_CASE("ThrowOnly, ComputeSqrt_Computesresult_WhenCalledWithPositiveArg")
{
    const auto result{compute_sqrt(4.0)};
    CHECK(result == Approx(2.0));
}


TEST_CASE("ThrowOnly, ComputeSqrt_Throws_WhenCalledWithNegativeArg")
{
    CHECK_THROWS_AS(compute_sqrt(-4.0), std::out_of_range);
}


TEST_CASE("ThrowOnly, AllocateDoubleArray_ReturnsArray_WhenArgsAreValid")
{
    auto result{allocate_double_array(10)};
    CHECK(result != nullptr);
}


TEST_CASE("ThrowOnly, AllocateDoubleArray_Throws_WhenArgsAreInvalid")
{
    CHECK_THROWS_AS(allocate_double_array(200), std::bad_alloc);
}


TEST_CASE("ThrowOnly, CreateArray_CreatesArray")
{
    constexpr int size{20};
    const auto result{create_array(size)};
    constexpr int delta{size / 2};

    for (int i{0}; i < delta; ++i) {
        CHECK(result[i] == Approx(delta - i));
    }

    for (int i{delta}; i < size; ++i) {
        CHECK(result[i] == Approx(i - delta));
    }
}
