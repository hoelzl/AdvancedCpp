// ReSharper disable CppClangTidyCppcoreguidelinesProBoundsPointerArithmetic
// ReSharper disable CppClangTidyCppcoreguidelinesAvoidCArrays
#pragma once

#include <array>
#include <iostream>
#include <memory>
#include <span>
#include <typeinfo>
#include <vector>

#define USE_TEMPLATES 1

struct MyBase
{
    explicit MyBase(int x) : x{x} {}

    int x;

    MyBase& inc()
    {
        x += 1;
        return *this;
    }
};

struct MyDerived : public MyBase
{
    MyDerived(int x, int y) : MyBase{x}, y{y} {}
    int y;
};

inline void print_array(const MyBase arr[], std::size_t len)
{
    std::cout << "MyBase[]: " << typeid(arr).name() << std::endl;
    for (std::size_t i = 0; i < len; ++i) {
        std::cout << arr[i].x << std::endl;
    }
}

inline void print_array_contents_via_pointer(const MyBase* arr, std::size_t len)
{
    std::cout << "MyBasePtr: " << typeid(arr).name() << std::endl;
    for (std::size_t i = 0; i < len; ++i) {
        std::cout << arr[i].x << std::endl;
    }
}

inline void print_contents_of_base_array()
{
    const MyBase arr[]{MyBase{1}, MyBase{2}, MyBase{3}};
    print_array(arr, 3);
    print_array_contents_via_pointer(arr, 3);
}

inline void print_contents_of_derived_array()
{
    const MyDerived arr[]{MyDerived{1, 10}, MyDerived{2, 20}, MyDerived{3, 30}};
    print_array(arr, 3);
    print_array_contents_via_pointer(arr, 3);
}

#if !USE_TEMPLATES
inline void print_std_array(std::array<MyBase, 3> arr)
{
    std::cout << "array<MyBase>: " << typeid(arr).name() << std::endl;
    for (const MyBase& elt : arr) {
        std::cout << elt.x << std::endl;
    }
}

#else
template <typename T>
void print_std_array(std::array<T, 3> arr)
{
    std::cout << "array<T>: " << typeid(arr).name() << std::endl;
    for (const T& elt : arr) {
        std::cout << elt.x << std::endl;
    }
}
#endif

inline void print_contents_of_base_std_array()
{
    const std::array<MyBase, 3> arr{MyBase{1}, MyBase{2}, MyBase{3}};
    print_std_array(arr);
}

inline void print_contents_of_derived_std_array()
{
    const std::array<MyDerived, 3> arr{
        MyDerived{1, 10}, MyDerived{2, 20}, MyDerived{3, 30}};
#if USE_TEMPLATES
    print_std_array(arr);
#endif
}

using MyBasePtr = std::unique_ptr<MyBase>;
using MyDerivedPtr = std::unique_ptr<MyDerived>;

#if !USE_TEMPLATES
void print_std_array_of_pointer(const char* prefix, const std::array<MyBasePtr, 3>& arr)
{
    std::cout << "Array<MyBasePtr> (" << prefix << "): " << typeid(arr).name()
              << std::endl;
    for (const MyBasePtr& elt : arr) {
        std::cout << elt->x << std::endl;
    }
}

#else
template <typename T, std::size_t n>
void print_std_array_of_pointer(const char* prefix, const std::array<T, n>& arr)
{
    std::cout << "Array<T*> (" << prefix << "): " << typeid(arr).name() << std::endl;
    for (const T& elt : arr) {
        std::cout << elt->x << std::endl;
    }
}
#endif

inline void print_contents_of_base_std_array_of_pointer()
{
    const std::array<MyBasePtr, 3> arr{
        std::make_unique<MyBase>(1), std::make_unique<MyBase>(2),
        std::make_unique<MyBase>(3)};
    print_std_array_of_pointer("base", arr);
}

inline void print_contents_of_derived_std_array_of_pointer()
{
    const std::array<MyDerivedPtr, 3> arr{
        std::make_unique<MyDerived>(1, 10), std::make_unique<MyDerived>(2, 20),
        std::make_unique<MyDerived>(3, 30)};
#if USE_TEMPLATES
    print_std_array_of_pointer("derived", arr);
#endif
}

inline void print_contents_of_mixed_std_array_of_pointer()
{
    const std::array<MyBasePtr, 3> arr{
        std::make_unique<MyBase>(1), std::make_unique<MyDerived>(2, 20),
        std::make_unique<MyBase>(3)};
    print_std_array_of_pointer("mixed", arr);
}

inline void print_span_of_pointer(const char* prefix, const std::span<MyBasePtr>& span)
{
    std::cout << "Span<MyBasePtr> (" << prefix << "): " << typeid(span).name()
              << std::endl;
    for (const MyBasePtr& elt : span) {
        std::cout << elt->x << std::endl;
    }
}


inline void print_contents_of_mixed_span()
{
    std::array<MyBasePtr, 3> arr1{
        std::make_unique<MyBase>(1), std::make_unique<MyDerived>(2, 20),
        std::make_unique<MyBase>(3)};
    MyBasePtr arr2[]{
        std::make_unique<MyBase>(1), std::make_unique<MyDerived>(2, 20),
        std::make_unique<MyBase>(3), std::make_unique<MyDerived>(4, 40),
        std::make_unique<MyDerived>(5, 50)};
    std::vector<MyBasePtr> vec{};

    for (MyBasePtr& elt : arr2) {
        std::cout << typeid(*elt).name() << std::endl;
        auto ptr{std::make_unique<MyBase>(*elt)};
        ptr->inc();
        vec.emplace_back(std::move(ptr));
    }

    print_span_of_pointer("mixed", std::span<MyBasePtr>{arr1});
    print_span_of_pointer("arr2", std::span<MyBasePtr>{arr2});
    print_span_of_pointer("vec", std::span<MyBasePtr>{vec.data(), vec.size()});
    print_span_of_pointer("arr2", std::span<MyBasePtr>{arr2});
}


inline void print_polymorphic_array_examples()
{
    print_contents_of_base_array();
    print_contents_of_derived_array();
    print_contents_of_base_std_array();
    print_contents_of_derived_std_array();
    print_contents_of_base_std_array_of_pointer();
    print_contents_of_derived_std_array_of_pointer();
    print_contents_of_mixed_std_array_of_pointer();
    print_contents_of_mixed_span();
}
