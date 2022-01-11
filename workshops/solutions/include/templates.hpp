#pragma once
#ifndef TEMPLATES_HPP
#define TEMPLATES_HPP

#include <compare>

namespace templates {
template <typename T>
T sum(T lhs, T rhs)
{
    return lhs + rhs;
}

struct TestClass
{
    TestClass(int i) : val{i} {}
    //operator int() const { return val; }

    int val{0};

    TestClass operator+(TestClass rhs) const { return {val + rhs.val}; }
    TestClass operator+(int rhs) const { return {rhs + val}; }
    auto operator<=>(const TestClass& rhs) const = default;
};

template <typename T1, typename T2>
std::common_type_t<T1, T2> sum2(T1 lhs, T2 rhs)
{
    return lhs + rhs;
}

} // namespace templates

#endif // TEMPLATES_HPP