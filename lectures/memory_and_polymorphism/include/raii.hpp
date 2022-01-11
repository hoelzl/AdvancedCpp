#pragma once
#ifndef RAII_HPP
#define RAII_HPP

#include <utility>
#include <gsl/gsl>

namespace raii {

template <typename T>
requires std::is_pointer_v<T>
struct DefaultDeleter
{
    // ReSharper disable once CppParameterMayBeConstPtrOrRef
    void operator()(gsl::owner<T> ptr) const { delete ptr; }
};

// A simple RAII container modeled somehow after std::unique_ptr<T> (but only
// for pointers and with built-in std::make_unique()).
template <typename T, template<typename> typename Deleter = DefaultDeleter>
class SimpleRaiiContainer
{
public:
    // Perfect forwarding of the constructor's arguments.
    template <typename... Ts>
    explicit SimpleRaiiContainer(Ts&&... args)
        : resource_{new T{std::forward<Ts>(args)...}}
    {}

    T* get() { return resource_; }
    const T* get() const { return resource_; }

    SimpleRaiiContainer(const SimpleRaiiContainer& other) = delete;
    SimpleRaiiContainer(SimpleRaiiContainer&& other) noexcept = default;
    SimpleRaiiContainer& operator=(const SimpleRaiiContainer& other) = delete;
    SimpleRaiiContainer& operator=(SimpleRaiiContainer&& other) noexcept = default;
    ~SimpleRaiiContainer() { deleter_(resource_); }

private:
    gsl::owner<T*> resource_{};
    Deleter<T*> deleter_{};
};

} // namespace raii

#endif // RAII_HPP