// ReSharper disable CppUnusedIncludeDirective
#include "resources.hpp"

#include "catch2/catch_test_macros.hpp"
#include <type_traits>

// Only enable this code when we demonstrate the effect, since it (deliberately)
// contains code problems that I don't want to silence for the whole project and this
// messes up the analysis reports.
#if 0
#define MY_CHECK(expr, check) ((check) ? [&] { CHECK(expr); }() : (void)(expr))

constexpr bool
test_fake_raii_container(bool check = false, bool disable_self_checks = false)
{
    auto* my_number = new int{7};

    auto my_container = res::fake_raii_container<int>{my_number};
    my_container.disable_self_checks = disable_self_checks;

    MY_CHECK(my_container.get(), check);
    MY_CHECK(*my_container.get() == 7, check);

    res::fake_raii_container<int> your_container{std::move(my_container)};
    your_container.disable_self_checks = disable_self_checks;

    // Deliberately using a moved-from object to check that we are correctly clearing
    // the pointer.
    MY_CHECK(!my_container.get(), check);
    MY_CHECK(your_container.get(), check);
    MY_CHECK(*your_container.get() == 7, check);

    your_container = std::move(your_container);
    MY_CHECK(your_container.get(), check);
    MY_CHECK(*your_container.get() == 7, check);

    auto his_container = res::fake_raii_container<int>{nullptr};
    his_container.disable_self_checks = disable_self_checks;

    his_container = std::move(your_container);

    MY_CHECK(!my_container.get(), check);
    MY_CHECK(!your_container.get(), check);
    MY_CHECK(his_container.get(), check);
    MY_CHECK(*his_container.get() == 7, check);

    return true;
}

TEST_CASE("Fake RAII.") { test_fake_raii_container(true, false); }

TEST_CASE("Check static properties.")
{
    STATIC_CHECK(std::is_move_assignable_v<res::fake_raii_container<int>>);
}

TEST_CASE("Compile-time evaluation with STATIC_CHECK.")
{
    STATIC_CHECK(test_fake_raii_container(false, false));
}

#endif
