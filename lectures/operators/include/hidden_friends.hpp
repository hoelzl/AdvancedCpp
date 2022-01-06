// ReSharper disable CppNonExplicitConvertingConstructor
// ReSharper disable CppClangTidyHicppExplicitConversions

#pragma once
#ifndef OPERATORS_HIDDEN_FRIENDS_HPP
#define OPERATORS_HIDDEN_FRIENDS_HPP
#include <string>

namespace ops {

// Don't even do this...
struct CompareMeHiddenFriends
{
    CompareMeHiddenFriends() = default;
    CompareMeHiddenFriends(const std::string& s) : id{std::stoi(s)} {}
    CompareMeHiddenFriends(int id) : id{id} {}
    int id{};

    friend bool operator==(const CompareMeHiddenFriends& lhs, const CompareMeHiddenFriends& rhs) noexcept;
    friend bool operator!=(const CompareMeHiddenFriends& lhs, const CompareMeHiddenFriends& rhs) noexcept;
    friend bool operator<(const CompareMeHiddenFriends& lhs, const CompareMeHiddenFriends& rhs) noexcept;
    friend bool operator<=(const CompareMeHiddenFriends& lhs, const CompareMeHiddenFriends& rhs) noexcept;
    friend bool operator>(const CompareMeHiddenFriends& lhs, const CompareMeHiddenFriends& rhs) noexcept;
    friend bool operator>=(const CompareMeHiddenFriends& lhs, const CompareMeHiddenFriends& rhs) noexcept;
};

} // namespace ops

#endif