// ReSharper disable CppClangTidyCppcoreguidelinesAvoidNonConstGlobalVariables
#include "raii.hpp"

#include <catch2/catch_test_macros.hpp>


template <typename T>
requires std::is_pointer_v<T>
struct TestDeleter
{
    // ReSharper disable once CppParameterMayBeConstPtrOrRef
    void operator()(gsl::owner<T> ptr) const
    {
        deleted_address = reinterpret_cast<uintptr_t>(ptr);
        delete ptr;
    }
    static std::uintptr_t deleted_address;
};

template <typename T>
requires std::is_pointer_v<T> std::uintptr_t TestDeleter<T>::deleted_address {};

TEST_CASE("SimpleRaiiContainer deletes its member.")
{
    TestDeleter<int*>::deleted_address = 0;
    {
        raii::SimpleRaiiContainer<int, TestDeleter> container{2};
        CHECK(TestDeleter<int*>::deleted_address == 0);
    }
    CHECK(TestDeleter<int*>::deleted_address != 0);
}

struct CannotCopy
{
    explicit CannotCopy(int val) : val{val} {}
    CannotCopy(const CannotCopy& other) = delete;
    CannotCopy(CannotCopy&& other) noexcept = default;
    CannotCopy& operator=(const CannotCopy& other) = delete;
    CannotCopy& operator=(CannotCopy&& other) noexcept = default;
    ~CannotCopy() = default;
    int val;
};

struct CanNeitherMoveNorCopy
{
    int& val_ref;
};

TEST_CASE("SimpleRaiiContainer forwands its constructor args.")
{
    using Type = std::pair<CannotCopy, CanNeitherMoveNorCopy>;
    TestDeleter<Type*>::deleted_address = 0;
    int j{1};
    {
        raii::SimpleRaiiContainer<Type, TestDeleter> container{1, j};
        CHECK(TestDeleter<Type*>::deleted_address == 0);
    }
    CHECK(TestDeleter<Type*>::deleted_address != 0);
}

TEST_CASE("SimpleRaiiContainer::get() works.")
{
    using Type = std::pair<CannotCopy, CanNeitherMoveNorCopy>;
    int j{23};
    raii::SimpleRaiiContainer<Type> container{3, j};
    CHECK(container.get()->first.val == 3);
    CHECK(container.get()->second.val_ref == 23);
}

TEST_CASE("SimpleRaiiContainer::get() returns mutable values.")
{
    using Type = std::pair<CannotCopy, CanNeitherMoveNorCopy>;
    int j{23};
    raii::SimpleRaiiContainer<Type> container{3, j};
    REQUIRE(container.get()->first.val == 3);
    CHECK_NOTHROW(container.get()->first.val = 100);
    CHECK(container.get()->first.val == 100);
}

TEST_CASE("SimpleRaiiContainer::get() const works.")
{
    using Type = std::pair<CannotCopy, CanNeitherMoveNorCopy>;
    int j{234};
    const raii::SimpleRaiiContainer<Type> container{4, j};
    CHECK(container.get()->first.val == 4);
    CHECK(container.get()->second.val_ref == 234);
    // Compiler error!
    // container.get()->first.val = 10;
}
