#pragma once
#ifndef CONCEPTS_HPP
#define CONCEPTS_HPP

#include <cstring>
#include <memory>
#include <type_traits>

namespace ct_concepts {

template <typename T>
constexpr auto max_fun_templ_1(T x, T y)
{
    return y < x ? x : y;
}


template <typename T>
auto max_fun_templ_2(T x, T y)
{
    return y < x ? x : y;
}

template <>
inline auto max_fun_templ_2(const char* x, const char* y)
{
    return std::strcmp(x, y) >= 0 ? x : y;
}

template <typename T>
auto max_fun_templ_3(T x, T y)
{
    return y < x ? x : y;
}

template <typename T>
auto max_fun_templ_3(T* x, T* y)
{
    return *y < *x ? *x : *y;
}

template <>
inline auto max_fun_templ_3(const char* x, const char* y)
{
    return std::strcmp(x, y) >= 0 ? x : y;
}

} // namespace ct_concepts

#endif // CONCEPTS_HPP