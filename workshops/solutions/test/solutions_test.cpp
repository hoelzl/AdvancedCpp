#include "solutions.hpp"

#include "catch2/catch_test_macros.hpp"

using namespace sol;

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

TEST_CASE("remove_duplicates()")
{
    std::vector<int> v{1, 3, 2, 5, 2, 2, 1};
    remove_duplicates(v);
    CHECK(v == std::vector{1, 2, 3, 5});
}

TEST_CASE("without_duplicates()")
{
    const std::vector<int> v{1, 3, 2, 5, 2, 2, 1};
    std::set<int> result = without_duplicates(v);
    CHECK(result == std::set{1, 2, 3, 5});
}
