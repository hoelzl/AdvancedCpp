#pragma once
#ifndef NONTYPE_TEMPLATES_HPP
#define NONTYPE_TEMPLATES_HPP

#include <string>
#include <vector>

namespace templates {

// We have seen how to use lambdas to configure computations:

inline auto make_adder(int n)
{
    return [n](int m) { return m + n; };
}

// We can use templates for a similar purpose (but now the value is fixed at
// compile time). For this, we use a non-type template parameter:

template <int N>
int add(int m)
{
    return m + N;
}

// This is particularly useful for algorithms.

// Nontype template parameters can also be used with classes:

template <int Copies = 1>
struct DocumentDistributor
{
    static std::vector<std::string> distribute(std::string document)
    {
        std::vector<std::string> result{};
        for (auto i{0}; i < Copies; ++i) {
            result.push_back(document);
        }
        return result;
    }
};

/// Mini-Workshop: Implement a generic class FixedStack that has the same
/// interface as the stack classes in file class_templates.hpp but takes a
/// maximal size as an additional nontype template parameter. Implement this
/// type using a container with fixed storage size.

} // namespace templates

#endif // NONTYPE_TEMPLATES_HPP