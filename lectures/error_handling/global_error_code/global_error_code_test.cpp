// ReSharper disable CppClangTidyCppcoreguidelinesAvoidCArrays
#include "global_error_code.hpp"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

using Catch::Approx;

using namespace global_error_code;

TEST_CASE("GlobalErrorCode, DomainError_SetsErrorCode")
{
    domain_error();
    CHECK(errno == EDOM);
}


TEST_CASE("GlobalErrorCode, OutOfMemoryError_SetsErrorCode")
{
    out_of_memory_error();
    CHECK(errno == ENOMEM);
}


TEST_CASE("GlobalErrorCode, ComputeSum_ComputesSumOfArguments")
{
    double result{};
    CHECK(compute_sum(2.0, 5.0, result));
    CHECK(result == Approx(7.0));
}


TEST_CASE("GlobalErrorCode, "
          "ComputeSqrt_ComputesresultAndDoesNotSetErrorCode_WhenCalledWithZeroArg")
{
    double result{};
    CHECK(compute_sqrt(0.0, result));
    CHECK(result == Approx(0.0));
}


TEST_CASE("GlobalErrorCode, "
          "ComputeSqrt_ComputesresultAndDoesNotSetErrorCode_WhenCalledWithPositiveArg")
{
    double result{};
    CHECK(compute_sqrt(4.0, result));
    CHECK(result == Approx(2.0));
}


TEST_CASE("GlobalErrorCode, ComputeSqrt_SetsErrorCode_WhenCalledWithNegativeArg")
{
    double result{};
    CHECK_FALSE(compute_sqrt(-4.0, result));
    CHECK(errno == EDOM);
}


TEST_CASE("GlobalErrorCode, AllocateDoubleArray_ReturnsArray_WhenArgsAreValid")
{
    std::unique_ptr<double[]> result{};
    REQUIRE(result.get() == nullptr);

    CHECK(allocate_double_array(10, result));
    CHECK(result.get() != nullptr);
}


TEST_CASE("GlobalErrorCode, AllocateDoubleArray_SetsErrorCode_WhenArgsAreInvalid")
{
    std::unique_ptr<double[]> result{};

    CHECK_FALSE(allocate_double_array(200, result));
    CHECK(errno == ENOMEM);
}


TEST_CASE("GlobalErrorCode, CreateArray_CreatesArray")
{
    constexpr int size{20};
    std::unique_ptr<double[]> result{};

    const bool success{create_array(size, result)};
    constexpr int delta{size / 2};
    REQUIRE(success);

    for (int i{0}; i < delta; ++i) {
        CHECK(result[i] == Approx(delta - i));
    }

    for (int i{delta}; i < size; ++i) {
        CHECK(result[i] == Approx(i - delta));
    }
}
