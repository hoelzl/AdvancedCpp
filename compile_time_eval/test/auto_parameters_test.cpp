#include "auto_parameters.hpp"

#include <catch2/catch_test_macros.hpp>
#include <numeric>
#include <string>

using namespace auto_params;
using namespace std::literals::string_literals;

namespace {
struct S
{
    [[maybe_unused]] int i{};
    [[maybe_unused]] int j{};
    auto operator<=>(const S& rhs) const = default;
};
} // namespace


TEST_CASE("max_lambda()")
{
    constexpr auto val1{max_lambda(1, 2)};
    CHECK(val1 == 2);

    constexpr auto val2{max_lambda(6, 2)};
    CHECK(val2 == 6);

    constexpr auto val3{max_lambda(4.0, 3.5)};
    CHECK(val3 == 4.0);

    // This works but confuses Intellisense
    // constexpr auto val4{
    //     max_lambda(std::string{"abc"}, std::string{"def"}) == std::string{"def"}};
    // CHECK(val4);

    CHECK(max_lambda("abc"s, "def"s) == "def"s);

    constexpr auto val5{max_lambda(S{3, 1}, S{1, 3})};
    CHECK(val5 == S{3, 1});

    constexpr auto val6{max_lambda(1, 2.0)};
    CHECK(val6 == 2.0);

    constexpr auto val7{max_lambda(1.0, 2)};
    CHECK(val7 == 2.0);
}


TEST_CASE("max_fun()")
{
    constexpr auto val1{max_fun(1, 2)};
    CHECK(val1 == 2);

    constexpr auto val2{max_fun(6, 2)};
    CHECK(val2 == 6);

    constexpr auto val3{max_fun(4.0, 3.5)};
    CHECK(val3 == 4.0);

    // This works but confuses Intellisense
    // constexpr auto val4{
    //     max_fun(std::string{"abc"}, std::string{"def"}) == std::string{"def"}};
    // CHECK(val4);

    CHECK(max_fun("abc"s, "def"s) == "def"s);

    constexpr auto val5{max_fun(S{3, 1}, S{1, 3})};
    CHECK(val5 == S{3, 1});

    constexpr auto val6{max_fun(1, 2.0)};
    CHECK(val6 == 2.0);

    constexpr auto val7{max_fun(1.0, 2)};
    CHECK(val7 == 2.0);
}

TEST_CASE("max_fun_templ()")
{
    constexpr auto val1{max_fun_templ(1, 2)};
    CHECK(val1 == 2);

    constexpr auto val2{max_fun_templ(6, 2)};
    CHECK(val2 == 6);

    constexpr auto val3{max_fun_templ(4.0, 3.5)};
    CHECK(val3 == 4.0);

    // This works but confuses Intellisense
    // constexpr auto val4{
    //    max_fun_templ(std::string{"abc"}, std::string{"def"}) == std::string{"def"}};
    // CHECK(val4);

    CHECK(max_fun_templ("abc"s, "def"s) == "def"s);

    constexpr auto val5{max_fun_templ(S{3, 1}, S{1, 3})};
    CHECK(val5 == S{3, 1});

    constexpr auto val6{max_fun_templ(1, 2.0)};
    CHECK(val6 == 2.0);

    constexpr auto val7{max_fun_templ(1.0, 2)};
    CHECK(val7 == 2.0);
}

TEST_CASE("Different behaviors (part 1)")
{
    const auto my_numbers{std::vector<uint32_t>{1, 8, 3, 25, 5}};
    const std::vector<std::string> my_strings{"abc"s, "def"s, "foo"s, "bar"s};

    CHECK(
        std::accumulate(std::cbegin(my_numbers), std::cend(my_numbers), 0u, max_lambda)
        == 25);

    CHECK(
        std::accumulate(cbegin(my_strings), cend(my_strings), ""s, max_lambda)
        == "foo"s);

    // Does not compile!
    // CHECK(
    //    std::accumulate(std::cbegin(my_numbers), std::cend(my_numbers), 0, max_fun)
    //    == 25);

    CHECK(
        std::accumulate(
            std::cbegin(my_numbers), std::cend(my_numbers), 0u, max_fun<int, int>)
        == 25);

    CHECK(
        std::accumulate(
            cbegin(my_strings), cend(my_strings), ""s,
            max_fun<const std::string&, const std::string&>)
        == "foo"s);
}

TEST_CASE("Different behaviors (part 2)")
{
    // Specify template arguments:
    CHECK(max_fun<int, int>(3, 7) == 7);

    // Specifying template arguments for lambdas is more complicated:
    CHECK(max_lambda.operator()<int, int>(3, 7) == 7);

    // Another method of calling a lambda with the desired argument types:
    CHECK([](int x, int y) { return max_lambda(x, y); }(3, 7) == 7);
}

TEST_CASE("Different behaviors (part 3)", "[.]")
{
    const std::vector<const char*> my_strings{"abc", "def", "foo", "bar"};

    // Oops
    CHECK(
        std::accumulate(cbegin(my_strings), cend(my_strings), "", max_lambda)
        == "foo"s);

    // Oops again, but maybe the error is more visible...
    CHECK(
        std::accumulate(
            cbegin(my_strings), cend(my_strings), "", max_fun<const char*, const char*>)
        == "foo"s);
}

TEST_CASE("Different behaviors (part 4)")
{
    const std::vector<const char*> my_strings{"abc", "def", "foo", "bar"};

    CHECK(
        std::accumulate(cbegin(my_strings), cend(my_strings), ""s, max_lambda)
        == "foo"s);

    CHECK(
        std::accumulate(
            cbegin(my_strings), cend(my_strings), ""s,
            max_fun<const std::string&, const std::string&>)
        == "foo"s);

    // If you want to be explicit about types with a lambda:
    CHECK(
        std::accumulate(
            cbegin(my_strings), cend(my_strings), ""s,
            [](const std::string& lhs, const std::string& rhs) {
                return max_lambda(lhs, rhs);
            })
        == "foo"s);

    // If you're slightly crazy:
    CHECK(
        std::accumulate(
            cbegin(my_strings), cend(my_strings), ""s,
            [](const std::string& lhs, const std::string& rhs) {
                return max_lambda.operator()<const std::string&, const std::string&>(
                    lhs, rhs);
            })
        == "foo"s);
}
