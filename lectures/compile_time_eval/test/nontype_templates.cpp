#include "nontype_templates.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace templates;
using namespace std::string_literals;

TEST_CASE("Adder using lambdas")
{
    auto add5{make_adder(5)};
    CHECK(add5(10) == 15);
}

TEST_CASE("Addition using templates") { CHECK(add<5>(10) == 15); }

TEST_CASE("Algorithm with template")
{
    std::vector<int> numbers{1, 2, 3, 4, 5};
    std::vector<int> result{};
    std::vector<int> expected{6, 7, 8, 9, 10};

    std::ranges::transform(numbers, std::back_inserter(result), add<5>);

    CHECK(result == expected);
}

TEST_CASE("DocumentDistributor")
{
    auto result = DocumentDistributor<3>::distribute("doc"s);
    CHECK(result == std::vector<std::string>{"doc"s, "doc"s, "doc"s});
}
