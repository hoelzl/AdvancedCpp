#include "types_expected.hpp"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <string>

using Catch::Approx;


using namespace types_expected;
using namespace std::string_literals;


TEST_CASE("TypesExpected, ComputeSum_ComputesSumOfArgumentsAndReturnsvalue")
{
    auto result{compute_sum(2.0, 5.0)};
    CHECK(static_cast<bool>(result));
    CHECK(*result == Approx(7.0));
}


TEST_CASE(
    "TypesExpected, ComputeSqrt_ComputesresultAndReturnsvalue_WhenCalledWithZeroArg")
{
    auto result{compute_sqrt(0.0)};
    CHECK(static_cast<bool>(result));
    CHECK(*result == Approx(0.0));
}


TEST_CASE("TypesExpected, "
          "ComputeSqrt_ComputesresultAndReturnsvalue_WhenCalledWithPositiveArg")
{
    auto result{compute_sqrt(4.0)};
    CHECK(static_cast<bool>(result));
    CHECK(*result == Approx(2.0));
}


TEST_CASE("TypesExpected, ComputeSqrt_ReturnsErrorCode_WhenCalledWithNegativeArg")
{
    auto result{compute_sqrt(-4.0)};
    CHECK_FALSE(static_cast<bool>(result));
    CHECK(result.error() == "Cannot compute square root of negative number."s);
}


TEST_CASE("TypesExpected, AllocateDoubleArray_ReturnsArray_WhenArgsAreValid")
{
    auto result{allocate_double_array(10)};
    CHECK(static_cast<bool>(result));
    CHECK(*result != nullptr);
}


TEST_CASE("TypesExpected, AllocateDoubleArray_ReturnsErrorCode_WhenArgsAreInvalid")
{
    auto result{allocate_double_array(200)};
    CHECK_FALSE(static_cast<bool>(result));
    CHECK(result.error() == "Cannot allocate double[] with size > 100."s);
}


TEST_CASE("TypesExpected, CreateArray_CreatesArray")
{
    constexpr int size{20};
    auto result{create_array(size)};
    constexpr int delta{size / 2};

    REQUIRE(result.has_value());

    for (int i{0}; i < delta; ++i) {
        CHECK(result.value()[i] == Approx(delta - i));
    }

    for (int i{delta}; i < size; ++i) {
        CHECK(result.value()[i] == Approx(i - delta));
    }
}
