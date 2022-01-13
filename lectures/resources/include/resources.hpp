// ReSharper disable CppClangTidyCppcoreguidelinesOwningMemory

#pragma once
#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <span>
#include <gsl/gsl>

namespace res {

void write_greeting(std::string_view name);

int add_ints(std::span<int> ints);

template <typename T>
class FakeRaiiContainer
{
public:
    explicit constexpr FakeRaiiContainer(const gsl::owner<const T*> resource, bool disable_self_checks = false)
        : disable_self_checks{disable_self_checks}, resource_{resource}
    {}

    FakeRaiiContainer(const FakeRaiiContainer& other) = delete;

    constexpr FakeRaiiContainer(FakeRaiiContainer&& other) noexcept
        : resource_{other.resource_}
    {
        if (disable_self_checks || this != &other) {
            other.resource_ = nullptr;
        }
    }

    FakeRaiiContainer& operator=(const FakeRaiiContainer& other) = delete;

    constexpr FakeRaiiContainer& operator=(FakeRaiiContainer&& other) noexcept
    {
        if (disable_self_checks || this != &other) {
            resource_ = other.resource_;
            other.resource_ = nullptr;
        }
        return *this;
    }

    constexpr ~FakeRaiiContainer() { delete resource_; }

    [[nodiscard]] constexpr const int* get() const { return resource_; }

    // Demonstrate: Tests will fail if this is not initialized.
    bool disable_self_checks{false};  // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)

private:
    gsl::owner<const T*> resource_{nullptr};
};

} // namespace res

#endif // RESOURCES_HPP
