#include "catch2/catch_test_macros.hpp"
#include "constexpr_demo.hpp"

#include <stdexcept>

constexpr bool test_if_constexpr_and_is_constant_evaluated()
{
    if constexpr (
        std::is_constant_evaluated()) { // NOLINT(clang-diagnostic-constant-evaluated)
        return true;
    }
    else {
        return false;
    }
}

TEST_CASE("if constexpr and std::is_constant_evaluated!!!")
{
    constexpr bool constexpr_result = test_if_constexpr_and_is_constant_evaluated();
    // ReSharper disable once CppVariableCanBeMadeConstexpr
    bool const non_constexpr_result = test_if_constexpr_and_is_constant_evaluated();
    CHECK(constexpr_result);

    // !!! Oops !!!
    CHECK(non_constexpr_result);
}

constexpr bool test_if_consteval()
{
    // Not yet supported by VC++...
    //if consteval {
    //    return true;
    //}
    //else {
    //    return false;
    //}
    return false;
}
