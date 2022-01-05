#pragma once
#ifndef AUTO_PARAMETERS_HPP
#define AUTO_PARAMETERS_HPP

namespace auto_params {

// Since C++14:
constexpr auto max_lambda_1 = [](auto x, auto y) {
    return y < x ? x : y;
};

// Since C++20:
constexpr auto max_fun(auto x, auto y)
{
    return y < x ? x : y;
}

// Since forever (almost)...
template <typename T1, typename T2>
constexpr auto max_fun_templ(T1 x, T2 y)
{
    return y < x ? x : y;
}

}

#endif // AUTO_PARAMETERS_HPP