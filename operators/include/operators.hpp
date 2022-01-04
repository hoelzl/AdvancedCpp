// ReSharper disable CppNonExplicitConvertingConstructor
// ReSharper disable CppClangTidyHicppExplicitConversions

#pragma once
#ifndef OPERATORS_OPERATORS_HPP
#define OPERATORS_OPERATORS_HPP

#include <string>

namespace ops {

// Don't do this...
struct CompareMe
{
    CompareMe() = default;
    CompareMe(std::string const& s) : id{std::stoi(s)} {}
    CompareMe(int id) : id{id} {}
    int id{};
};

[[nodiscard]] bool operator==(CompareMe const& lhs, CompareMe const& rhs) noexcept;
[[nodiscard]] bool operator!=(CompareMe const& lhs, CompareMe const& rhs) noexcept;
[[nodiscard]] bool operator<(CompareMe const& lhs, CompareMe const& rhs) noexcept;
[[nodiscard]] bool operator<=(CompareMe const& lhs, CompareMe const& rhs) noexcept;
[[nodiscard]] bool operator>(CompareMe const& lhs, CompareMe const& rhs) noexcept;
[[nodiscard]] bool operator>=(CompareMe const& lhs, CompareMe const& rhs) noexcept;


// Don't do this, either...
struct CompareMeMember
{
    CompareMeMember() = default;
    CompareMeMember(std::string const& s) : id{std::stoi(s)} {}
    CompareMeMember(int id) : id{id} {}
    int id{};

    [[nodiscard]] bool operator==(CompareMeMember const& rhs) const noexcept;
    [[nodiscard]] bool operator!=(CompareMeMember const& rhs) const noexcept;
    [[nodiscard]] bool operator<(CompareMeMember const& rhs) const noexcept;
    [[nodiscard]] bool operator<=(CompareMeMember const& rhs) const noexcept;
    [[nodiscard]] bool operator>(CompareMeMember const& rhs) const noexcept;
    [[nodiscard]] bool operator>=(CompareMeMember const& rhs) const noexcept;
};


} // namespace ops

#endif // OPERATORS_OPERATORS_HPP
