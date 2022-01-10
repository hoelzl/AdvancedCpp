// ReSharper disable CppClangTidyCppcoreguidelinesAvoidNonConstGlobalVariables
// ReSharper disable CppClangTidyCppcoreguidelinesAvoidCArrays
#pragma once
#ifndef CLASS_TEMPLATES_HPP
#define CLASS_TEMPLATES_HPP

#include <stdexcept>
#include <vector>

namespace templates {

template <typename T>
class Stack
{
public:
    // T can be used like any other type. We can even use it to construct values
    // (although this default argument is not a good idea!)
    void push(const T& elem = T{});
    void pop();
    [[nodiscard]] const T& top() const;
    [[nodiscard]] bool empty() const;

    // We can simply write Stack to refer to Stack<T> inside the class, and
    // inside member function definitions.
    //
    // This is certainly not a good idea, though!
    //
    // The definition of the storage for default_stack can be in the header file
    // itself, since it always has external linkage.
    static Stack default_stack;

    // Functions that are not used will not be instantiated:
    void do_not_use_me() { elems_.do_something_terrible(); }

private:
    std::vector<T> elems_{};
};

// When defining functions outside of the class definition, we need to provide
// the template parameters. Also note, that the template parameter has to be
// specified in angle brackets after the class name.
//
// These definitions can not be moved to the .cpp file.
template <typename T>
void Stack<T>::push(const T& elem)
{
    elems_.push_back(elem);
}

template <typename T>
void Stack<T>::pop()
{
    if (elems_.empty()) {
        throw std::logic_error{"Cannot get pop an empty stack."};
    }
    elems_.pop_back();
}

template <typename T>
const T& Stack<T>::top() const
{
    if (elems_.empty()) {
        throw std::logic_error{"Cannot get top of an empty stack."};
    }
    return elems_.back();
}

template <typename T>
bool Stack<T>::empty() const
{
    return elems_.empty();
}

template <typename T>
Stack<T> Stack<T>::default_stack{};

///////////////////////////////////////////////////////////////
/// Mini Workshop: Implement the class RingBuffer from a previous workshop as a
/// generic type.
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////

// You can specialize generic types for individual type parameters:

struct IntWrapper
{
    int my_int;
    auto operator<=>(const IntWrapper& rhs) const = default;
};

template <>
class Stack<IntWrapper>
{
public:
    void push(const IntWrapper& elem = IntWrapper{}) { elems_.push_back(elem.my_int); }

    void pop()
    {
        if (!elems_.empty()) {
            elems_.pop_back();
        }
    }

    [[nodiscard]] IntWrapper top() const
    {
        if (elems_.empty()) {
            return {0};
        }
        return {elems_.back()};
    }

    [[nodiscard]] bool empty() const { return elems_.empty(); }

private:
    std::vector<int> elems_{};
};


///////////////////////////////////////////////////////////////

// Classes can also be partially specialized:


template <typename T>
class Stack<T*>
{
public:
    // T can be used like any other type. We can even use it to construct values
    // (although this default argument is not a good idea!)
    void push(T* elem);
    T* pop();
    [[nodiscard]] T* top() const;
    [[nodiscard]] bool empty() const;

private:
    std::vector<T*> elems_{};
};

// When defining functions outside of the class definition, we need to provide
// the template parameters. Also note, that the template parameter has to be
// specified in angle brackets after the class name.
//
// These definitions can not be moved to the .cpp file.
template <typename T>
void Stack<T*>::push(T* elem)
{
    elems_.push_back(elem);
}

template <typename T>
T* Stack<T*>::pop()
{
    if (elems_.empty()) {
        throw std::logic_error{"Cannot get pop an empty stack."};
    }
    T* result{elems_.back()};
    elems_.pop_back();
    return result;
}

template <typename T>
T* Stack<T*>::top() const
{
    if (elems_.empty()) {
        throw std::logic_error{"Cannot get top of an empty stack."};
    }
    return elems_.back();
}

template <typename T>
bool Stack<T*>::empty() const
{
    return elems_.empty();
}

///////////////////////////////////////////////////////////////

// Specializing multiple type parameters:
template <typename T1, typename T2>
struct MyClass
{
    [[nodiscard]] static std::string info() { return "<T1, T2>"; }
};

template <typename T>
struct MyClass<T, T>
{
    [[nodiscard]] static std::string info() { return "<T, T>"; }
};

template <typename T>
struct MyClass<T, int>
{
    [[nodiscard]] static std::string info() { return "<T, int>"; }
};

template <typename T1, typename T2>
struct MyClass<T1*, T2*>
{
    [[nodiscard]] static std::string info() { return "<T1*, T2*>"; }
};

///////////////////////////////////////////////////////////////
/// Mini Workshop:
///
/// Write a generic class Pair<> that can store two arbitrary values, which can
/// be accessed using Pair::first() and Pair::second(). Define specializations
/// for storing unsigned short values that store not the value itself but an
/// unsigned int that contains the value shifted to the left by 2 positions (and
/// shift the value back when retrieving it). Which changes do you need to make
/// to the interface? How many overloads do you need?
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////

// We can provide default arguments for template parameters. This allows us to,
// e.g., define a Stack that can take different "storage backends". We also
// allow automated deduction of class template parameters for this stack (CTAD,
// class template argument deduction).

template <typename T, typename Elems = std::vector<T>>
class StackV2
{
public:
    StackV2() = default;
    explicit StackV2(const T& elem) : elems_{{elem}} {}

    void push(const T& elem);
    void pop();
    [[nodiscard]] const T& top() const;
    [[nodiscard]] bool empty() const;

private:
    Elems elems_{};
};

template <typename T, typename Elems>
void StackV2<T, Elems>::push(const T& elem)
{
    elems_.push_back(elem);
}

template <typename T, typename Elems>
void StackV2<T, Elems>::pop()
{
    if (elems_.empty()) {
        throw std::logic_error{"Cannot get pop an empty stack."};
    }
    elems_.pop_back();
}

template <typename T, typename Elems>
const T& StackV2<T, Elems>::top() const
{
    if (elems_.empty()) {
        throw std::logic_error{"Cannot get top of an empty stack."};
    }
    return elems_.back();
}

template <typename T, typename Elems>
bool StackV2<T, Elems>::empty() const
{
    return elems_.empty();
}

StackV2(const char*)->StackV2<std::string, std::vector<std::string>>;


///////////////////////////////////////////////////////////////

// Template template version of the stack, to avoid specifying the element type
// twice

template <typename T, template <typename> typename Elems = std::vector>
class StackV3
{
public:
    StackV3() = default;
    explicit StackV3(const T& elem) : elems_{{elem}} {}

    void push(const T& elem);
    void pop();
    [[nodiscard]] const T& top() const;
    [[nodiscard]] bool empty() const;

private:
    Elems<T> elems_{};
};

template <typename T, template <typename> typename Elems>
void StackV3<T, Elems>::push(const T& elem)
{
    elems_.push_back(elem);
}

template <typename T, template <typename> typename Elems>
void StackV3<T, Elems>::pop()
{
    if (elems_.empty()) {
        throw std::logic_error{"Cannot get pop an empty stack."};
    }
    elems_.pop_back();
}

template <typename T, template <typename> typename Elems>
const T& StackV3<T, Elems>::top() const
{
    if (elems_.empty()) {
        throw std::logic_error{"Cannot get top of an empty stack."};
    }
    return elems_.back();
}

template <typename T, template <typename> typename Elems>
bool StackV3<T, Elems>::empty() const
{
    return elems_.empty();
}


///////////////////////////////////////////////////////////////

// How do we declare operators that need access to the class internals?
// (a) Declare the template implicitly:

template <typename T>
struct WidgetV1
{
    T my_t{};

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const WidgetV1<U>& w);
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const WidgetV1<T>& w)
{
    os << w.my_t << " V1";
    return os;
}

// (b) Forward declare, but then you need to forward declare the widget before
// that:

template <typename T>
struct WidgetV2;

template <typename T>
std::ostream& operator<<(std::ostream& os, const WidgetV2<T>& w);


template <typename T>
struct WidgetV2
{
    T my_t{};

    friend std::ostream& operator<<<T>(std::ostream& os, const WidgetV1<T>& w);
};


template <typename T>
std::ostream& operator<<(std::ostream& os, const WidgetV2<T>& w)
{
    os << w.my_t << " V2";
    return os;
}


} // namespace templates

#endif // CLASS_TEMPLATES_HPP