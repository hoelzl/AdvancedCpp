// ReSharper disable CppClangTidyCppcoreguidelinesAvoidCArrays
#include "error_code_with_query.hpp"

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

using Catch::Approx;

using namespace error_code_with_query;

TEST_CASE("ErrorCodeWithQuery")
{
    clear_status();

    SECTION("ErrorCodeWithQuery, DomainError_SetsErrorCode")
    {
        domain_error();
        CHECK(get_status() == Status::domain_error);
    }


    SECTION("ErrorCodeWithQuery, OutOfMemoryError_SetsErrorCode")
    {
        out_of_memory_error();
        CHECK(get_status() == Status::out_of_memory_error);
    }


    SECTION("ErrorCodeWithQuery, ClearStatus_ClearsStatus")
    {
        domain_error();
        REQUIRE(get_status() == Status::domain_error);

        clear_status();
        CHECK(get_status() == Status::none);
    }


    SECTION(
        "ErrorCodeWithQuery, ComputeSum_ComputesSumOfArgumentsAndDoesNotSetErrorCode")
    {
        CHECK(compute_sum(2.0, 5.0) == Approx(7.0));
        CHECK(get_status() == Status::none);
    }


    SECTION("ErrorCodeWithQuery, "
            "ComputeSqrt_ComputesresultAndDoesNotSetErrorCode_WhenCalledWithZeroArg")
    {
        CHECK(compute_sqrt(0.0) == Approx(0.0));
        CHECK(get_status() == Status::none);
    }


    SECTION(
        "ErrorCodeWithQuery, "
        "ComputeSqrt_ComputesresultAndDoesNotSetErrorCode_WhenCalledWithPositiveArg")
    {
        CHECK(compute_sqrt(4.0) == Approx(2.0));
        CHECK(get_status() == Status::none);
    }


    SECTION("ErrorCodeWithQuery, ComputeSqrt_SetsErrorCode_WhenCalledWithNegativeArg")
    {
        CHECK(compute_sqrt(-4.0) == 0.0);
        CHECK(get_status() == Status::domain_error);
    }


    SECTION("ErrorCodeWithQuery, AllocateIntArray_ReturnsArray_WhenArgsAreValid")
    {
        std::unique_ptr<double[]> result{allocate_double_array(10)};
        CHECK(result.get() != nullptr);
    }


    SECTION("ErrorCodeWithQuery, AllocateIntArray_SetsErrorCode_WhenArgsAreInvalid")
    {
        std::unique_ptr<double[]> result{allocate_double_array(200)};
        CHECK(get_status() == Status::out_of_memory_error);
    }


    SECTION("ErrorCodeWithQuery, CreateArray_CreatesArray")
    {
        constexpr int size{20};
        auto result{create_array(size)};
        int delta{size / 2};

        for (int i{0}; i < delta; ++i) {
            CHECK(result[i] == Approx(delta - i));
        }

        for (int i{delta}; i < size; ++i) {
            CHECK(result[i] == Approx(i - delta));
        }
    }
}
