// Copyright (c) 2021 Dr. Matthias Hölzl.

// ReSharper disable CppUnusedIncludeDirective
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "advanced_cpp.hpp"

#include <cassert>

#include "doctest.hpp"

// Only enable this code when we demonstrate the effect, since it (deliberately)
// contains code problems that I don't want to silence for the whole project and this
// messes up the analysis reports.
#if 0
#define STATIC_CHECK(expr, check) ((check) ? [&] { CHECK(expr); }() : assert(expr))


constexpr bool test_fake_raii_container(bool check = false, bool disable_self_checks = false)
{
    auto* my_number = new int{7};

    auto my_container = fake_raii_container<int>{my_number};
    my_container.disable_self_checks = disable_self_checks;

    STATIC_CHECK(my_container.get(), check);
    STATIC_CHECK(*my_container.get() == 7, check);

    fake_raii_container<int> your_container{std::move(my_container)};
    your_container.disable_self_checks = disable_self_checks;

    // Deliberately using a moved-from object to check that we are correctly clearing
    // the pointer.
    STATIC_CHECK(!my_container.get(), check);
    STATIC_CHECK(your_container.get(), check);
    STATIC_CHECK(*your_container.get() == 7, check);

    your_container = std::move(your_container);
    STATIC_CHECK(your_container.get(), check);
    STATIC_CHECK(*your_container.get() == 7, check);

    auto his_container = fake_raii_container<int>{nullptr};
    his_container.disable_self_checks = disable_self_checks;

    his_container = std::move(your_container);

    STATIC_CHECK(!my_container.get(), check);
    STATIC_CHECK(!your_container.get(), check);
    STATIC_CHECK(his_container.get(), check);
    STATIC_CHECK(*his_container.get() == 7, check);

    return true;
}

static_assert(test_fake_raii_container(false, false));

TEST_CASE("Fake RAII") { test_fake_raii_container(true, false); }


#endif