// ReSharper disable CppClangTidyCppcoreguidelinesOwningMemory
#pragma once

#include <span>
#include <gsl/gsl>

void write_greeting(std::string_view name);

int add_ints(std::span<int> ints);

template <typename T>
class fake_raii_container
{
public:
    explicit constexpr fake_raii_container(
        gsl::owner<T const*> const resource, bool disable_self_checks = false)
        : disable_self_checks{disable_self_checks}, resource_{resource}
    {}

    fake_raii_container(fake_raii_container const& other) = delete;

    constexpr fake_raii_container(fake_raii_container&& other) noexcept
        : resource_{other.resource_}
    {
        if (disable_self_checks || this != &other) {
            other.resource_ = nullptr;
        }
    }

    fake_raii_container& operator=(fake_raii_container const& other) = delete;

    constexpr fake_raii_container& operator=(fake_raii_container&& other) noexcept
    {
        if (disable_self_checks || this != &other) {
            resource_ = other.resource_;
            other.resource_ = nullptr;
        }
        return *this;
    }

    constexpr ~fake_raii_container() { delete resource_; }

    [[nodiscard]] constexpr int const* get() const { return resource_; }

    // Demonstrate: Tests will fail if this is not initialized.
    bool disable_self_checks{false};

private:
    gsl::owner<T const*> resource_{nullptr};
};
