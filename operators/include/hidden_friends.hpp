// ReSharper disable CppNonExplicitConvertingConstructor
// ReSharper disable CppClangTidyHicppExplicitConversions

#pragma once
#ifndef OPERATORS_HIDDEN_FRIENDS_HPP
#define OPERATORS_HIDDEN_FRIENDS_HPP
#include <string>

namespace ops {

struct CompareMeHiddenFriends
{
    CompareMeHiddenFriends() = default;
    CompareMeHiddenFriends(std::string const& s) : id{std::stoi(s)} {}
    CompareMeHiddenFriends(int id) : id{id} {}
    int id{};


    friend bool operator==(CompareMeHiddenFriends const& lhs, CompareMeHiddenFriends const& rhs);
    friend bool operator!=(CompareMeHiddenFriends const& lhs, CompareMeHiddenFriends const& rhs);
    friend bool operator<(CompareMeHiddenFriends const& lhs, CompareMeHiddenFriends const& rhs);
    friend bool operator<=(CompareMeHiddenFriends const& lhs, CompareMeHiddenFriends const& rhs);
    friend bool operator>(CompareMeHiddenFriends const& lhs, CompareMeHiddenFriends const& rhs);
    friend bool operator>=(CompareMeHiddenFriends const& lhs, CompareMeHiddenFriends const& rhs);

};

} // namespace ops

#endif