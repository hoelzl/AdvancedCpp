// ReSharper disable CppNonExplicitConvertingConstructor
// ReSharper disable CppClangTidyHicppExplicitConversions

#pragma once
#ifndef OPERATORS_OPERATORS_HPP
#define OPERATORS_OPERATORS_HPP

#include <string>

namespace ops {

struct CompareMe
{
    CompareMe() = default;
    CompareMe(std::string const& s) : id{std::stoi(s)} {}
    CompareMe(int id) : id{id} {}
    int id{};
};

bool operator==(CompareMe const& lhs, CompareMe const& rhs);
bool operator!=(CompareMe const& lhs, CompareMe const& rhs);
bool operator<(CompareMe const& lhs, CompareMe const& rhs);
bool operator<=(CompareMe const& lhs, CompareMe const& rhs);
bool operator>(CompareMe const& lhs, CompareMe const& rhs);
bool operator>=(CompareMe const& lhs, CompareMe const& rhs);


struct CompareMeMember
{
    CompareMeMember() = default;
    CompareMeMember(std::string const& s) : id{std::stoi(s)} {}
    CompareMeMember(int id) : id{id} {}
    int id{};

    bool operator==(CompareMeMember const& rhs) const;
    bool operator!=(CompareMeMember const& rhs) const;
    bool operator<(CompareMeMember const& rhs) const;
    bool operator<=(CompareMeMember const& rhs) const;
    bool operator>(CompareMeMember const& rhs) const;
    bool operator>=(CompareMeMember const& rhs) const;
};


} // namespace ops

#endif // OPERATORS_OPERATORS_HPP
