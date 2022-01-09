// ---
// jupyter:
//   jupytext:
//     formats: cpp:light
//     text_representation:
//       extension: .cpp
//       format_name: light
//       format_version: '1.5'
//       jupytext_version: 1.13.5
//   kernelspec:
//     display_name: C++17
//     language: C++17
//     name: xcpp17
// ---

// + [markdown] slideshow={"slide_type": "slide"}
// # The Standard Template Library

// + [markdown] slideshow={"slide_type": "slide"}
// ## STL Containers
//
// - Sequence containers
//     - Elements are identified by their indices
// - Associative containers
//     - Elements are identified by their keys
//     - Ordered
//     - Unordered
// - Container adaptors
// - (Iterators)
// - (Algorithms)
// -

// ## Operations on (almost) all Containers
//
// (See [cppreference.com](https://en.cppreference.com/w/cpp/container) for a more detailed overview.)
//
// - Type aliases:
//     - `iterator`
//     - `const_iterator`
//     - `size_type`
//     - `difference_type`
//     - `value_type`
//     - `reference`
//     - `const_reference`

// + [markdown] slideshow={"slide_type": "slide"}
// ## Type Aliases
//
// A Type alias introduces a new name that refers to an existing type (similar to `typedef`):
//
// ```c++
// using new_type = existing_type;
// ```
//
// Often used in standard classes to hide implementation details:
//
// ```c++
// // Not standard vector: no template
// class nostd::vector {
//   using iterator = __internal_iterator_type;
//   ...
// }
// ```
// You can use this shorthand declare iterators for vectors:
//
// ```c++
// for (nostd::vector::iterator it{v.begin()}; it != v.end(); ++v) { /* ... */ }
// ```

// + [markdown] slideshow={"slide_type": "subslide"}
// It is often beneficial to use the same pattern in user-defined types:
//
// ```c++
// class MyThing {
//    using MyWidgets = MySpecialCollectionType<MyWidget>;
// }
// ```
// This makes it, e.g., easier to change `MySpecialCollectionType` to another type if the need arises. (Provided the new type shares most of the operations with `MySpecialCollectionType`.
//
// ```c++
// MyWidgets ws{};
// for (w : ws) { /* ... */ }
// ```
// -

// ## Operations on (almost) all Containers (cont.)
//
// - Construction
//     - default, copy, move
//     - from iterator range \[`beg`, `end`)
//     - from initializer list `{x, y, z, ...}`
// - Iterators
//     - `c.begin()`, `c.end()`
//     - `c.cbegin()`, `c.cend()`

// + slideshow={"slide_type": "subslide"}
#import <vector>
// -

std::vector<int> v1{};
v1

std::vector<int> v2{1, 2, 3, 4};
v2

std::vector<int> v3{++(v2.begin()), v2.end()};
v3

// ## Operations on (almost) all Containers (cont.)
//
// - Assignment
//     - from same type
//     - from initializer list
// - Swap
//     - `c1.swap(c2)`
//     - `swap(c1, c2)` (equivalent)
// - Relational operators
//     - `==`, `!=`
//     - `<`, `<=`, `>`, `>=`

// + slideshow={"slide_type": "subslide"}
v1 = v3;
v1
// -

v3 = {2, 4, 5, 6, 12};
v3

v1.swap(v2);
v1

v2

// + slideshow={"slide_type": "subslide"}
v1 >= v2
// -

v1 < v2

swap(v1, v2);
v1 < v2

// ## Operations on (almost) all Containers (cont.)
//
// - Size
//     - `c.empty()`
//     - `c.size()`
//     - `c.max_size()`
// - Adding/removing elements (except `array`)
//     - `c.clear(...)`
//     - `c.insert(...)`
//     - `c.emplace(...)`
//     - `c.erase(...)`

// + slideshow={"slide_type": "subslide"}
v1.empty()
// -

v1.size()

v1.max_size()

v1.clear();
v1.empty()    

// + [markdown] slideshow={"slide_type": "slide"}
// ## Ranges: Iterable Types
//
// - It is often useful to make types iterable, in particular more utility-focused types
// - For this types need to provide only `begin()` and `end()` member functions
//     - (We need to clarify how iterators work, though)
// - With this many STL algorithms can be applied to the type and it can be used in range-based for loops
// - Often `begin()` and `end()` simply delegate to a member of the type
// - In C++20 this is formalized by the [`std::ranges::range` concept](https://en.cppreference.com/w/cpp/ranges/range).

// + [markdown] slideshow={"slide_type": "subslide"}
// ### The `range` Concept
//
// ```c++
// template <typename T>
// concept range = requires(T& t) {
//   std::ranges::begin(t); // equality-preserving for forward iterators
//   std::ranges::end  (t);
// };
// ```
//
// The function [`std::ranges::begin()`](https://en.cppreference.com/w/cpp/ranges/begin) returns `t.begin()` if this is possible, similarly for [`std::ranges::end()`](https://en.cppreference.com/w/cpp/ranges/end). The value returned by `std::ranges::end()` is sometimes called a *sentinel*.

// + [markdown] slideshow={"slide_type": "slide"}
// ## Range-based For Loop
//
// Why can we loop over our `Board` with a range-based for loop?
//
// ```c++
// for ([init-statement;] range-declaration : range-expression)
//     loop-statement 
// ```
//
// expands into
//
// ```c++
// {
//     init-statement
//     auto&& __range = range-expression;
//     auto __begin = __range.begin();
//     auto __end = __range.end();
//     for ( ; __begin != __end; ++__begin) {
//         range-declaration = *__begin;
//         loop-statement
//     }
// } 
// ```
// **Beware!** If `range-expression` returns a reference it is dangling: "\[A\] temporary bound to a reference parameter in a function call exists until the end of the full expression containing that function call: if the function returns a reference, which outlives the full expression, it becomes a dangling reference." ([cppreference.com](https://en.cppreference.com/w/cpp/language/reference_initialization))
//
//

// + [markdown] slideshow={"slide_type": "slide"}
// ## TTT: Board
//
// - Allow users to iterate over `Board` instances
// - Make the class `Board` usable by STL algorithms

// + [markdown] slideshow={"slide_type": "slide"}
// ## Mini Workshop: Inefficient `IntRange`
//
// Define a class `IntRangeV0` with the following partial signature:
// ```c++
// class IntRange {
//     IntRange(int min, int max);
//     /* ... */
// }
// ```
// such that
// ```c++
// for (const int i : IntRangeV0{10, 20}) {
//     std::cout << i << "\n";
// }
// ```
// prints the numbers 10 to 20 on `std::cout`. To achieve this, store all numbers between `min` and `max` in a vector insided the `IntRange` instance.
//
// Test your implementation using Catch2.
//
// *Note:* You can use the project `workshops/starter_kit/` to implement your solution.

// + [markdown] slideshow={"slide_type": "slide"}
// ## Overview of Container Types
//
// Different container types have different trade-offs and functionality.
//
// Operations are typically only defined for container types for which they are efficiently implementable.

// + [markdown] slideshow={"slide_type": "slide"}
// ### Sequence Containers
//
// Operations such as
//
// - `front()`
// - `back()`
// - `operator[]`
// - `resize()`
// - `push_back()`, `pop_back()`
//
// are availble for most sequence containers (where they make sense).

// + [markdown] slideshow={"slide_type": "subslide"}
// ### Sequence Containers 
//
// - `array`: the one trick pony (but it's very good at that trick)
//     - fixed size
//     - fast random access
//     - all memory can be stack-allocated

// + slideshow={"slide_type": "subslide"}
#include <array>
#include <iostream>
// -

std::array<int, 5> a1{1, 2, 3};
for (int i : a1)
    std::cout << i << ", ";

std::array<int, 5> a2{a1};
std::array<int, 5> a3;
a3 = a1;
for (int i : a3)
    std::cout << i << ", ";

// + [markdown] slideshow={"slide_type": "slide"}
// ### Sequence Containers 
//
// - `vector`: the workhorse
//     - holds elements in contiguous memory
//     - fast random access
//     - insertion/deletion efficient only at back
// - `deque`: the dark horse
//     - holds elements in contiguous memory
//     - fast random access
//     - insertion/deletion efficient at front and back
// -

// ### Functionality of Vector and Deque
//
// - `c.push_back(elt)`
// - `c.emplace_back(...)`
// - `c.pop_back()`
// - `c.insert(...)`, `c.emplace(...)`
//
// Deque also has
// - `c.push_front(elt)`
// - `c.emplace_front(...)
// - `c.pop_front()`

// + [markdown] slideshow={"slide_type": "slide"}
// ### Sequence Containers
//
// - Lists: more one trick ponies (although they're often not great)
//     - store their elements in linked nodes
//     - no random access
//     - insertion/deletion in middle efficient
//
// - `forward_list`
//     - can iterate in only one direction
//
// - `list`
//     - can iterate in both directions

// + [markdown] slideshow={"slide_type": "slide"}
// ## Mini Workshop:  `RingBuffer`
//
// Define a class `RingBuffer` with member functions
//
// - `bool RingBuffer::empty()` that returns `true` if the buffer is empty, `false` otherwise
// - `void RingBuffer::put(int)` that puts an element into the buffer
// - `int RingBuffer::get()` that gets an element from a non-empty buffer
//
// `get()` should return the elements put into the buffer in "first in, first out" manner, but the buffer should store a maximum of `capacity` elements (configured at construction time) and drop the oldest elements when more than `capacity` elements are stored.
//
// For example, for a buffer `b` with `capacity` 2, the following should hold:
//
// ```c++
// b.put(1);
// b.put(2);
// b.get(); // -> 1
// b.put(3);
// b.put(4); // 2 is dropped
// b.get(); // -> 3
// ```
//
// Test your implementation using Catch2.
//
// *Note:* You can use the project `workshops/starter_kit/` to implement your solution.

// + [markdown] slideshow={"slide_type": "slide"}
// ### Ordered Associative Containers
//
// - `set`: collection of unique elements
// - `map`: dictionary mapping keys to values
// - `multiset`: a set with non-unique members
// - `multimap`: a dictionary with non-unique keys

// + [markdown] slideshow={"slide_type": "slide"}
// ### Unordered Associative Containers
//
// The unordered associative containers are similar to their ordered counterparts. They are often more efficient, but their members need to be hashable.
//
// - `unordered_set`
// - `unordered_map`
// - `unordered_multiset`
// - `unordered_multimap`

// + [markdown] slideshow={"slide_type": "slide"}
// ### Container Adaptors
//
// - `stack`
// - `queue`
// - `priority_queue`

// + [markdown] slideshow={"slide_type": "slide"}
// ## Lambdas
//
// We can overload `operator()` to create *functors*, i.e., objects that can be called:
// -

struct Functor {
    int operator()(int i) { return i * i; }
};
Functor f{};
f(3)

#include <type_traits>
std::is_class_v<decltype(f)>

int square(int i) { return i * i; }
std::is_class_v<decltype(square)>

std::is_object_v<decltype(square)>

std::is_object_v<decltype(f)>

typeid(f).name()

// + [markdown] slideshow={"slide_type": "subslide"}
// A *lambda expression* is a shorthand notation for a functor instance. The values of lambda expressions are called *closures* or (informally) *lambdas*.
//
// A lambda has an (anonymous) type defined by the compiler, called its *closure type*.

// + slideshow={"slide_type": "-"}
auto lambda = [](int i){ return i * i; };
lambda(3)
// -

#include <type_traits>
std::is_class_v<decltype(lambda)>

typeid(lambda).name()

lambda.operator()(12)

// + [markdown] slideshow={"slide_type": "subslide"}
// ### Non-top-level Lambdas
//
// In contrast to functions, lambdas can be defined inside other functions:
// -

int my_function() {
    auto lambda =[]() { return 1; };
    return lambda() + 1;
}
my_function() 

// + slideshow={"slide_type": "subslide"}
#include <functional>
#include <string>
std::function<std::string()> pick_function(int i) {
    if (i > 100) {
        return [] { return "You picked a large number."; };
    }
    else {
        return [] { return "You picked a small number."; };
    }
}
auto my_fun{pick_function(10)};
my_fun()
// -

pick_function(1000)()

// + [markdown] slideshow={"slide_type": "slide"}
// ### Generic Lambdas
//
// Lambdas may have parameters declared with type specifier `auto`. The types of these parameters is deduced according to the rules for template argument deduction.
//
// Such a lambda is called a *generic lambda*.
// -

// Cling dies if I try to do anything with generic lambdas on the top-level
template <typename T>
T call_generic_lambda(T arg1) {
    auto f = [](auto arg2) { return arg2 + arg2; };
    return f(arg1);
}

call_generic_lambda(123)

#include <string>
call_generic_lambda(std::string{"foo"})

// + [markdown] slideshow={"slide_type": "subslide"}
// A generic lambda results in a closure type with generic call operator, *not* a generic closure type:
//
// ```c++
// [](auto arg) { return arg + arg; }
// ```
// is equivalent to

// + slideshow={"slide_type": "-"}
struct MyClosure {
    template <typename T>
    T operator()(T arg) {
        return arg + arg;
    }
}
// -

MyClosure{}(123)

MyClosure{}(std::string{"foo"})

// + slideshow={"slide_type": "subslide"}
#include <utility>
template <typename T1, typename T2>
std::pair<T1, T2> call_generic_lambdas(T1 arg1, T2 arg2) {
    auto f = [](auto arg) { return arg + arg; };
    return std::pair<T1, T2>(f(arg1), f(arg2));
}
// -

call_generic_lambdas(123, std::string{"foo"}).first

call_generic_lambdas(123, std::string{"foo"}).second

// + [markdown] slideshow={"slide_type": "slide"}
// ## Mini Workshop:  `get_op_impl`
//
// Given the following enumeration:
// ```c++
// enum class Op { add, mul };
// ```
//
// write a function `get_op_impl(Op op)` that returns a callable with signature `int(int, int)` that can compute the following result:
//
// - $m + n$ if `op` is `add`
// - $m * n$ if `op` is `mul`

// + [markdown] slideshow={"slide_type": "subslide"}
// (Load `ce_get_op_impl.cpp` into [Compiler Explorer](https://godbolt.org/) or go to [this link](https://godbolt.org/z/rjzKhTYPY) to get the Compiler Explorer page for discussing this solution).
// -

// ## Type Erasure
//
// `std::function` is an example for *type erasure*, a way to treat objects with different types uniformly, as long as they provide a (partially) similar interface.
//
// (It can lead to results similar to "duck typing" in dynamic languages.)
//
// See `examples/stl/type_erasure.hpp`.

// + [markdown] slideshow={"slide_type": "slide"}
// ## Lambdas: Captures
//
// If lambdas are defined inside other function, we often want to access the local variable of the function inside the body of the lambda. This can be done by specifying which variables should be accessible inside the square brackets.
//
// (The square brackets are the *capture list*):
// -

int capture_1() {
    int i = 10;
    auto lambda = [i]{ return i; };
    i = 20;
    return lambda();
}
capture_1()

int capture_manually() {
    int i = 10;
    struct { int ci; int operator()() { return ci; }} lambda{i};
    i = 20;
    return lambda();
}
capture_manually()

// + [markdown] slideshow={"slide_type": "subslide"}
// We can capture by value (as above) or by reference, we can also capture all local values by value or reference:
// -

int capture_2() {
    int i = 10;
    auto lambda = [&i]{ return i; };
    i = 20;
    return lambda();
}
capture_2()

// + slideshow={"slide_type": "subslide"}
int capture_3() {
    int i = 10, j = 20;
    auto lambda = [=]{ return i + j; };
    i = 100;
    j = 200;
    return lambda();
}
capture_3()
// -

int capture_4() {
    int i = 10, j = 20;
    auto lambda = [&]{ return i + j; };
    i = 100;
    j = 200;
    return lambda();
}
capture_4()

// + [markdown] slideshow={"slide_type": "subslide"}
// We can combine these features to "create functions during runtime":
// -

auto make_adder(int n) {
    return [n](int m) { return m + n; };
}

// Need to wrap this in a function since Cling does not handle top-level captures.
int test_make_adder() {
    auto adder{make_adder(5)};
    return adder(3);
}
test_make_adder()

// + slideshow={"slide_type": "subslide"}
template <typename T>
int call_fun(T fun, int arg) {
    return fun(arg);
}
// -

call_fun([](int n) { return n + 1; }, 3)

call_fun(make_adder(2), 3)

// + [markdown] slideshow={"slide_type": "subslide"}
// #### Danger! Reference Captures may Dangle!
// -

auto make_bad_adder(int n) {
    return [&n](int m) { return m + n; };
}
//  Uh, oh.
call_fun(make_bad_adder(2), 3)

// + [markdown] slideshow={"slide_type": "slide"}
// ## Iterator Categories

// + [markdown] slideshow={"slide_type": "slide"}
// ## STL Algorithms
//
// The STL provides many generic algorithms that can be used with any type that satisfies the `range` concept. 
//
// Algorithms
//
// - take two iterators that form an iterator range
// - perform no container operation, i.e., they don't add or remove elements
// - may reorder or change the elements in the container

// + [markdown] slideshow={"slide_type": "subslide"}
// ### Examples for Algorithms
//
// #### Non Modifying
//
// - `all_of`: is a predicate true for all elements?
// - `for_each`: apply function to range
// - `count`, `count_if`: counts the number of elements satisfying specific criteria
// - `mismatch`: finds the first difference between two ranges
// - `find`, `find_if`: finds the first element satisfying specific criteria
// - `adjacent_find`: find first two equivalent adjacent items
// - `search`: search for a range of elements

// + [markdown] slideshow={"slide_type": "subslide"}
// #### Modifying Algorithms
//
// - `copy`, `copy_if`: copies a range
// - `copy_backward`: copies in backward order
// - `fill`: assigns a fixed value to all elements
// - `transform`: applies a function to a range, stores the result in a destination range
// - `generate`: repeatedly calls a function and stores the results in a range
// - `remove`, `remove_if`: "removes" elements satisfying specific criteria
// - `remove_copy`, `remove_copy_if`: copies elements not satisfying specific criteria
// - `replace[_copy][_if]`: replaces elements
// - `swap_ranges`: swaps two ranges
// - `shuffle` (deprecated), `random_shuffle`: shuffles a range
// - `sample`: selects random elements from a range
// - `unique`, `unique_copy`: "removes" consecutive copies of elements
// -

// #### Non-Range Algorithms
//
// - `swap`: swaps the values of two objects
// - `max`, `min`, `minmax`: extrema of multiple values
// - `clamp`: clamps a value between boundaries

// + [markdown] slideshow={"slide_type": "subslide"}
// ### Mini-Workshop: Sum of Integers
//
// Write a function `int sum_from_to(int min, int max)` that computes the sum of all numbers from `min` to `max` (inclusive). Use an `IntRangeV0` and an appropriate algorithm from the STL to perform the task.

// + [markdown] slideshow={"slide_type": "slide"}
// ## TTT: Extend the Board
//
// - Define a function `field_value(Position pos)` that retrieves the field at a given position
// - There are various ways to model positions, we'll use a `std::pair<short, short>` for now
// - Write tests that test the new functionality

// + [markdown] slideshow={"slide_type": "slide"}
// ## Using Tools: Address Sanitizer

// + [markdown] slideshow={"slide_type": "slide"}
// ## Static Variables
// -

//

// + [markdown] slideshow={"slide_type": "slide"}
// ## TTT: Valid Moves
//
// - Define a member function `Board::is_move_valid(Position pos)` that checks whether `pos` is empty
// - Define a member function `Board::valid_moves()` that returns a set of all valid moves.

// + [markdown] slideshow={"slide_type": "slide"}
// ## TTT: PlayerColor Class
//
// - Implement `operator<<` for `FieldValue`
// - Add a class `PlayerColor` with factory functions `from_string(std::string_view)` and `from_field_value(FieldValue)`
// - Write an implicit conversion operator from player color to field value
// - What happens if you try to compare player colors?
// - What happens if you try to write a player color to an output stream?

// + [markdown] slideshow={"slide_type": "slide"}
// ## User-defined Operators

// + [markdown] slideshow={"slide_type": "slide"}
// ## Argument Dependent Lookup

// + [markdown] slideshow={"slide_type": "slide"}
// ## Overload Resolution

// + [markdown] slideshow={"slide_type": "slide"}
// ## Exceptions and Error Handling

// + [markdown] slideshow={"slide_type": "slide"}
// ## TTT: Perform a move
//
// - Implement a method `Board::move(PlayerColor, Position)`
//

// + [markdown] slideshow={"slide_type": "slide"}
// ## TTT: Winning Configurations
//
// Let's call a set of three posistions a *configuration*.
//
// - Implement a member function `Board::configuration(PlayerColor pc)` that returns all positions occupied by `pc`
// - Implement a member function `Board::winning_configurations()` that returns the set of all winning configurations.
// - Implement a member function `Board::has_winning_configuration(PlayerColor pc)` that checks whether `pc` has a winning configuration.

// + [markdown] slideshow={"slide_type": "slide"}
// ## TTT: Printing the Board
//
// Implement functions:
// - `to_char(FieldValue)` that returns `' '`, `'x'`, and `'o'` for an empty, black or white field, respectively
// - `to_string(Board board, int prefix_len = 0)` that returns a representation of the board with `prefix_len` spaces indentation.
//
// -




