// Copyright (c) 2021 Dr. Matthias Hölzl.

// ReSharper disable CppUnusedIncludeDirective
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "advanced_cpp.hpp"

#include <cassert>

#include "doctest.hpp"

#define STATIC_CHECK(expr, check) ((check) ? [&]{ CHECK(expr); }() : assert(expr))

constexpr bool test_fake_raii_container(bool check = false)
{
    auto* my_number = new int{7};

    auto my_container = FakeRaiiContainer<int>{my_number};
    STATIC_CHECK(my_container.get(), check);
    STATIC_CHECK(*my_container.get() == 7, check);

    FakeRaiiContainer<int> your_container{std::move(my_container)};
    // Deliberately using a moved-from object to check that we are correctly clearing
    // the pointer.
    STATIC_CHECK(!my_container.get(), check);
    STATIC_CHECK(your_container.get(), check);
    STATIC_CHECK(*your_container.get() == 7, check);

    your_container = std::move(your_container);
    STATIC_CHECK(your_container.get(), check);
    STATIC_CHECK(*your_container.get() == 7, check);

    auto his_container = FakeRaiiContainer<int>{nullptr};
    his_container = std::move(your_container);

    STATIC_CHECK(!my_container.get(), check);
    STATIC_CHECK(!your_container.get(), check);
    STATIC_CHECK(his_container.get(), check);
    STATIC_CHECK(*his_container.get() == 7, check);

    return true;
}

static_assert(test_fake_raii_container());

TEST_CASE("Fake RAII") { test_fake_raii_container(true); }