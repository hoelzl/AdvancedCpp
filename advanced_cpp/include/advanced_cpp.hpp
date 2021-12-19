#pragma once

#include <gsl/gsl>

void write_greeting(std::string_view const name);

int add_ints(gsl::span<int> const ints);

template <typename T>
class FakeRaiiContainer
{
public:
    explicit constexpr FakeRaiiContainer(gsl::owner<T*> const the_resource)
        : the_resource{the_resource}
    {}

    FakeRaiiContainer(FakeRaiiContainer const& other) = delete;
    constexpr FakeRaiiContainer(FakeRaiiContainer&& other) noexcept
        : the_resource{other.the_resource}
    {
        if (this != &other) {
            other.the_resource = nullptr;
        }
    }

    FakeRaiiContainer& operator=(FakeRaiiContainer const& other) = delete;
    constexpr FakeRaiiContainer& operator=(FakeRaiiContainer&& other) noexcept
    {
        auto disable_self_check = false;
        if (disable_self_check || this != &other) {
            the_resource = other.the_resource;
            other.the_resource = nullptr;
        }
        return *this;
    }

    constexpr ~FakeRaiiContainer()
    {
        delete the_resource;
    }

    [[nodiscard]] constexpr int* get() const { return the_resource; }

private:
    gsl::owner<T*> the_resource{nullptr};
};
