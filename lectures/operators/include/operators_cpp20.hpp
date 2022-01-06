// ReSharper disable CppClangTidyHicppExplicitConversions
// ReSharper disable CppNonExplicitConvertingConstructor
#pragma once
#ifndef OPERATORS_CPP20_HPP
#define OPERATORS_CPP20_HPP
#include <compare>
#include <string>

namespace ops20 {

struct EqMe
{
    int id{};

    [[nodiscard]] bool operator==(const EqMe& rhs) const noexcept
    {
        return (id % 100) == (rhs.id % 100);
    }

    [[nodiscard]] bool operator==(int rhs) const noexcept
    {
        return (id % 100) == (rhs % 100);
    }

    [[nodiscard]] bool operator==(const std::string& rhs) const
    {
        return *this == std::stoi(rhs);
    }
};

struct OpSpaceship
{
    int id1{};
    int id2{};

    // Lexicographic memberwise comparison.
    [[nodiscard]] auto operator<=>(const OpSpaceship&) const = default;
};

struct CompareMe
{
    int id{};

    [[nodiscard]] bool operator==(const CompareMe& rhs) const noexcept
    {
        return (id % 100) == (rhs.id % 100);
    }

    [[nodiscard]] bool operator==(int rhs) const noexcept
    {
        return (id % 100) == (rhs % 100);
    }
    
    [[nodiscard]] auto operator<=>(const CompareMe& rhs) const noexcept
    {
        return (id % 100) <=> (rhs.id % 100);
    }

    [[nodiscard]] auto operator<=>(int rhs) const noexcept
    {
        return (id % 100) <=> (rhs % 100);
    }
    
};

} // namespace ops20

#endif // OPERATORS_CPP20_HPP