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
class fake_raii_container
{
public:
    explicit constexpr fake_raii_container(const gsl::owner<const T*> resource, bool disable_self_checks = false)
        : disable_self_checks{disable_self_checks}, resource_{resource}
    {}

    fake_raii_container(const fake_raii_container& other) = delete;

    constexpr fake_raii_container(fake_raii_container&& other) noexcept
        : resource_{other.resource_}
    {
        if (disable_self_checks || this != &other) {
            other.resource_ = nullptr;
        }
    }

    fake_raii_container& operator=(const fake_raii_container& other) = delete;

    constexpr fake_raii_container& operator=(fake_raii_container&& other) noexcept
    {
        if (disable_self_checks || this != &other) {
            resource_ = other.resource_;
            other.resource_ = nullptr;
        }
        return *this;
    }

    constexpr ~fake_raii_container() { delete resource_; }

    [[nodiscard]] constexpr const int* get() const { return resource_; }

    // Demonstrate: Tests will fail if this is not initialized.
    bool disable_self_checks{false};  // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)

private:
    gsl::owner<const T*> resource_{nullptr};
};

} // namespace res

#endif // RESOURCES_HPP
