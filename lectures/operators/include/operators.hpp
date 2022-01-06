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
    CompareMe(const std::string& s) : id{std::stoi(s)} {}
    CompareMe(int id) : id{id} {}
    int id{};
};

[[nodiscard]] bool operator==(const CompareMe& lhs, const CompareMe& rhs) noexcept;
[[nodiscard]] bool operator!=(const CompareMe& lhs, const CompareMe& rhs) noexcept;
[[nodiscard]] bool operator<(const CompareMe& lhs, const CompareMe& rhs) noexcept;
[[nodiscard]] bool operator<=(const CompareMe& lhs, const CompareMe& rhs) noexcept;
[[nodiscard]] bool operator>(const CompareMe& lhs, const CompareMe& rhs) noexcept;
[[nodiscard]] bool operator>=(const CompareMe& lhs, const CompareMe& rhs) noexcept;


// Don't do this, either...
struct CompareMeMember
{
    CompareMeMember() = default;
    CompareMeMember(const std::string& s) : id{std::stoi(s)} {}
    CompareMeMember(int id) : id{id} {}
    int id{};

    [[nodiscard]] bool operator==(const CompareMeMember& rhs) const noexcept;
    [[nodiscard]] bool operator!=(const CompareMeMember& rhs) const noexcept;
    [[nodiscard]] bool operator<(const CompareMeMember& rhs) const noexcept;
    [[nodiscard]] bool operator<=(const CompareMeMember& rhs) const noexcept;
    [[nodiscard]] bool operator>(const CompareMeMember& rhs) const noexcept;
    [[nodiscard]] bool operator>=(const CompareMeMember& rhs) const noexcept;
};


} // namespace ops

#endif // OPERATORS_OPERATORS_HPP
