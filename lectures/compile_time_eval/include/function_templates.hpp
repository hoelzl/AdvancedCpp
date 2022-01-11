#pragma once
#ifndef FUNCTION_TEMPLATES_HPP
#define FUNCTION_TEMPLATES_HPP
#include <cstring>
#include <type_traits>

namespace templates {

// Template parameter T
// - Can be used like a type inside the template
// - The template parameter is replaced by an actual type when the template is
//   instantiated
// - Instantiation happens automatically when the template is used
// - A separate version of the template is compiled for each instantiation
// - Template processing happens in two phases
//   - Definition time: checks that don't depend on template parameters
//   - Instantiation time: The complete code is checked
//
template <typename T>
T max_v1(T lhs, T rhs)
{
    return rhs < lhs ? lhs : rhs;
}

// When splitting declaration and definition, both must include the template
// parameters.
template <typename T>
T max_v1a(T lhs, T rhs);

template <typename T>
T max_v1a(T lhs, T rhs)
{
    return rhs < lhs ? lhs : rhs;
}


// T does not have to be the "complete" type
// - T is deduced to int in this case
// - For reference parameters the types must match exactly
// - For value parameters trivial conversions that decay apply:
//   - const/volatile ignored
//   - references convert to referenced type
//   - raw arrays/functions convert to pointers
template <typename T>
T max_v2(const T& lhs, const T& rhs)
{
    return rhs < lhs ? lhs : rhs;
}

// Mini-Workshop: Write a template function sum(lhs, rhs) that computes lhs +
// rhs for all types for which it is possible.
//
// Test the function with ints, doubles, strings and a user-defined class
// TestClass that overloads operator+. Can you instantiate sum() with arguments
// 1 and TestClass{} if you add overloads that take an int parameter to
// TestClass::operator+?

// If we want to match different argument types:
template <typename T1, typename T2>
auto max_v3(T1 lhs, T2 rhs)
{
    return rhs < lhs ? lhs : rhs;
}

// We could also manually specify the return type
//
// DANGER: It's easy to get this wrong. For example this does not what you
// probably expect.
//
// Calls to max_v4_bad() with rvalue arguments actually return references to the
// temporaries allocated on the stack which no longer exist when the function
// returns!
template <typename T1, typename T2>
auto max_v4_bad(T1 lhs, T2 rhs) -> decltype(true ? lhs : rhs)
{
    return rhs < lhs ? lhs : rhs; // NOLINT(clang-diagnostic-return-stack-address)
}

// It's common to decay the result type if it is inferred with decltype:
// (In C++<20 you need to prefix the return type with typename.)
// The definition of max_v3() worked because auto always decays.
template <typename T1, typename T2>
auto max_v4(T1 lhs, T2 rhs) -> std::decay_t<decltype(true ? lhs : rhs)>
{
    return rhs < lhs ? lhs : rhs;
}

// We can avoid the complications with decaying by using the std::common_type
// trait (which decays automatically):
template <typename T1, typename T2>
std::common_type_t<T1, T2> max_v5(T1 lhs, T2 rhs)
{
    return rhs < lhs ? lhs : rhs;
}

// Mini-Workshop: Redefine your function sum() to take two type parameters. Can
// you now call it with mixed arguments without specifying the types?

// Template parameters can take default values, just like function parameters.
// Default arguments can refer to parameters that appear to their left. With
// this we can allow users to explicitly specify the return type:

template <typename T1, typename T2, typename T3 = std::common_type_t<T1, T2>>
T3 max_v6(T1 lhs, T2 rhs)
{
    return rhs < lhs ? lhs : rhs;
}

// Templates participate in overload resolution. The main things to keep in mind
// are:
// - If a template and a non-template are an equally good match, the
//   non-template function is preferred
// - Templates are often exact matches; in that case even trivial conversions
//   lose against the template.

constexpr int template_version_called{1};
constexpr int non_template_version_called{2};

template <typename T>
int overload_v1(T, T)
{
    return template_version_called;
}

inline int overload_v1(int /*unused*/, int /*unused*/)
{
    return non_template_version_called;
}


template <typename T1, typename T2>
int overload_v2(T1, T2)
{
    return template_version_called;
}

inline int overload_v2(int /*unused*/, int /*unused*/)
{
    return non_template_version_called;
}

// We can combine overload resolution for templates with non-templates
template <typename T>
T max_v7(T lhs, T rhs)
{
    return rhs < lhs ? lhs : rhs;
}

template <typename T>
T max_v7(T* lhs, T* rhs)
{
    return *rhs < *lhs ? *lhs : *rhs;
}

inline const char* max_v7(const char* lhs, const char* rhs)
{
    return std::strcmp(rhs, lhs) < 0 ? lhs : rhs;
}

// Note that all overloads must be visible before a function is called,
// otherwise overload resolution will lead to unexpected results.

// (Maybe we should talk about call by value, std::ref and std::cref here.)

} // namespace templates

#endif // FUNCTION_TEMPLATES_HPP