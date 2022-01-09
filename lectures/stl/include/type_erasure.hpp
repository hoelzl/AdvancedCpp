// ReSharper disable CppClassCanBeFinal
#pragma once
#ifndef TYPE_ERASURE_HPP
#define TYPE_ERASURE_HPP

#include <concepts>
#include <memory>

namespace stl {

// Private!
class IntFunctionWrapperInterface // NOLINT(cppcoreguidelines-special-member-functions)
{
public:
    virtual int operator()(int m, int n) const = 0;
    virtual ~IntFunctionWrapperInterface() = default;
};

// Private!
template <std::invocable<int, int> FunT>
class IntFunctionWrapper : public IntFunctionWrapperInterface
{
public:
    explicit IntFunctionWrapper(FunT&& fun) : wrapped_fun_{std::move(fun)} {}
    int operator()(int m, int n) const override { return wrapped_fun_(m, n); }

private:
    FunT wrapped_fun_;
};

class BinaryIntFunction
{
public:
    template <std::invocable<int, int> FunT>
    explicit BinaryIntFunction(FunT fun)
        : fun_wrapper_{std::make_unique<IntFunctionWrapper<FunT>>(std::move(fun))}
    {}

    int operator()(int m, int n) const { return fun_wrapper_->operator()(m, n); }

private:
    std::unique_ptr<IntFunctionWrapperInterface> fun_wrapper_;
};

// More usual implementation:

template <typename T>
class BinaryFunction
{
public:
    template <std::invocable<T, T> FunT>
    // ReSharper disable once CppNonExplicitConvertingConstructor
    BinaryFunction(FunT fun)
        : fun_wrapper_{std::make_unique<FunctionWrapper<FunT>>(std::move(fun))}
    {}

    T operator()(T t1 = T{}, T t2 = T{}) const { return fun_wrapper_->call(t1, t2); }

private:
    struct FunctionWrapperInterface // NOLINT(cppcoreguidelines-special-member-functions)
    {
        [[nodiscard]] virtual T call(T m, T n) const = 0;
        virtual ~FunctionWrapperInterface() = default;
    };

    template <std::invocable<T, T> FunT>
    struct FunctionWrapper final : public FunctionWrapperInterface
    {
        explicit FunctionWrapper(FunT&& fun) : wrapped_fun{std::move(fun)} {}
        T call(T m, T n) const override { return wrapped_fun(m, n); }
        FunT wrapped_fun;
    };

    std::unique_ptr<FunctionWrapperInterface> fun_wrapper_;
};

} // namespace stl

#endif // TYPE_ERASURE_HPP