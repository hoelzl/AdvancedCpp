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
// # Functions and Lambdas

// + [markdown] slideshow={"slide_type": "slide"}
// ## Preliminaries: Example Projects
//
// The `AdvancedCpp` project contains a number of subfolders:
//
// - `notebooks`: the slides as Jupyter notebooks (to run with xeus-cling C++17 kernels)
// - `examples`: completed code for projects that we'll code together during the course (if you want to)
// - `codealong`: initial code for the projects in the `examples` folder
// - `workshops`: code for workshops that you'll be doing
//     - `workshops/starter_kit_xxx`: projects that you can use to solve the workshops
//     - `workshops/solutions_xxx`: solution for the workshops
// - `lectures`: code for demonstration purposes during the lectures where no live-coding takes place

// + [markdown] slideshow={"slide_type": "slide"}
// - All projects are built with CMake; dependencies for projects where they are needed are installed with [vcpkg](https://vcpkg.io/en/index.html).
// - I tried to organize the project so that all important subprojects can be built without additional dependencies.
// - `examples/advanced_cpp` is a prototypical project to demonstrate how all other subprojects are set up

// + [markdown] slideshow={"slide_type": "slide"}
// ## Preliminaries: Catch2
//
// In order to get working software we need to write tests as we build the system. In this course we use the [Catch2](https://github.com/catchorg/Catch2) framework for writing tests.
// -

// ### Organization of Tests
//
// Catch is very flexible, different styles of testing are supported. Here is how tests are set up for this course:
//
// - Tests are organized into test cases (`TEST_CASE`)
//     - Each test case has a title
//     - A test case can have optional tags (written as a single string)
// - Test cases can have sections (`SECTION`)
//     - Each section has a title and optionally a longer description
//     - Each section is executed independently of the others
// - Tests are compiled into an executable
//     - Each test case name must be unique in the executable or no test is run

// + [markdown] slideshow={"slide_type": "subslide"}
// - Tags 
//     - Are enclosed in square brackets, e.g., `[backend]` or `[slow]`
//     - Can be used to, run only a subset of the tests by passing them on the command line
//     - The special tag `[.]` causes tests to be skipped by default
// - By using `TEMPLATE_TEST_CASE` and its variants instead of `TEST_CASE`, tests can be executed for multiple types
// - BDD-style tests
//     - Instead of `TEST_CASE`, `SECTION` BDD-style macros can be used to structure tests:
//     - `SCENARIO` corresponds to `TEST_CASE`
//     - `GIVEN`, `WHEN`, and `THEN` correspond to `SECTION`

// + [markdown] slideshow={"slide_type": "subslide"}
// ### Test Assertions
//
// - Catch uses "natural expressions" for testing
//     - There is no need for a large number of specialized assertion macros
// - `REQUIRE(expression)` evaluates `expression`, logs the result, and aborts the test case if the result is false
// - `CHECK(expression)` evaluates `expression`, logs the result, but continues the test case even if `expression` evaluates to a false result
//
// There are some variants for special cases:
//
// - `*_FALSE()` variants expect the expression to evaluate to a false result
// - `*_NOTHROW()` expects no exception to be thrown but otherwise discards the result of the expression
// - `*_THROWS()` expects an exception of any type to be thrown
// - `*_THROWS_AS()` expects an exception of a specific type to be thrown
//
// Other macros provide, e.g., matchers for exception strings, etc.

// + [markdown] slideshow={"slide_type": "slide"}
// ## First Example: Tic Tac Toe
//
// Let's implement the game of tic-tac-toe in a procedural manner.
//
// ![tic-tac-toe](img/tic_tac_toe.png)
//
// We'll "overengineer" this solution to show off more features of C++.
// + [markdown] slideshow={"slide_type": "slide"}
// ## TTT: Field and Board
//
// - Define a scoped enumeration `FieldValue` representing the value of a field on the board
// - Define a class `Board` containing an array of 9 fields

// + [markdown] slideshow={"slide_type": "subslide"}
// ## Representing the Board
//
// - The board consists of 9 fields
// - We need a data structure with storage for exactly 9 values
// - What would you choose?

// + [markdown] slideshow={"slide_type": "subslide"}
// ### Class `std::array`
//
// - Alternative to built-in arrays
// - Almost always superior to built-in arrays(*):
//     - Does not decay, not interchangable with pointer
//     - Therefore, number of elements stays part of the type
//     - Invariant for polymorphic types
//     
// (*) In cases where you need a fixed-size storage

// + [markdown] slideshow={"slide_type": "slide"}
// ### Types, Objects, Values, Variables
//
// - A *type* restrict the operations for an entity and provides semantic meaning to its sequence of bits ([details](https://en.cppreference.com/w/cpp/language/type))
// - A *value* is a set of bits interpreted according to a type
// - An *object* is memory that holds a value of some type ([details](https://en.cppreference.com/w/cpp/language/object))
// - A *variable* is a named object

// + [markdown] slideshow={"slide_type": "slide"}
// ### Declarations and Definitions
//
// - A declaration is a statement that introduce names into a program ([details](https://en.cppreference.com/w/cpp/language/declarations))
// - A definition is a declaration that is sufficient to use the named entity
// - A name may have multiple declarations but generally only one definition

// + [markdown] slideshow={"slide_type": "slide"}
// ## Pointers
//
// Valid pointers can
//
// - point to an object or function (i.e., represent its address)
// - point to the location past the end of an object (i.e., represent the first byte after the end of the object)
// - be the null pointer (i.e., not point to any object)
//
// All other pointers are invalid.
// -

// ### Some Caveats
//
// - Pointers have no influence on the lifetime of an object; there is no way to check whether the pointed-to object is still alive
// - Pointers can be compared, but comparison with `<` is only defined for pointers to the same object
// - `std::less` guarantees a strict total order for arbitrary pointers. (Note that `std::less` is a class that must be instantiated)

// + slideshow={"slide_type": "subslide"}
#include <functional>
int i{2}, j{1};
// &i < &j // Probably works, but no guarantees
std::less{}(&i, &j)

// + slideshow={"slide_type": "subslide"}
int ia[5]{};
ia < &ia[3] // OK

// + [markdown] slideshow={"slide_type": "subslide"}
// ### Arrays and Pointers
//
// - In C++ arrays and pointers are very closely related
// - The *address-of* operator `&` can be applied to any object and returns a pointer
// - In many situations, arrays *decay* to pointers, i.e., they are (silently) converted into pointers without using the address-of operator
//

// + slideshow={"slide_type": "-"}
int ia[]{1, 2, 3, 4, 5};
int* pi{ia};
*(pi + 2)
// -

int plus1(int* pi) { return *pi + 1; }
plus1(ia)

// + [markdown] slideshow={"slide_type": "subslide"}
// When using `auto` with arrays they decay into pointers:
// -

auto pi2{ia}; // pi2 is an `int*` not an `int[]`

// + slideshow={"slide_type": "subslide"}
std::is_same_v<decltype(pi2), int[]>
// -

std::is_same_v<decltype(pi2), int*>

// + slideshow={"slide_type": "-"}
#include <type_traits>
std::is_same_v<decltype(pi2), decltype(ia)>
// -

std::is_same_v<decltype(pi2), decltype(pi)>

// + [markdown] slideshow={"slide_type": "subslide"}
// `decltype(entity-or-expression)` inspects the type of `entity-or-expression`:
//
// - `decltype(entity)` yields the type of `entity`, if `entity` is an identifier for a variable or a class member that is not enclosed in parentheses
// - otherwise `decltype(expression)` yields the type and value category of `expression` (using various forms of references)
//
// (This is a complex way of saying, it is important whether you enclose the argument of decltype in parentheses.)

// + slideshow={"slide_type": "subslide"}
const int* foo;
// The declared type of foo is const int*...
std::is_same_v<decltype(foo), const int*>
// -

// ... which is not a reference
std::is_same_v<decltype(foo), const int*&>

// But the expression foo is an lvalue...
std::is_same_v<decltype((foo)), const int*>

// ... therefore decltype returns a reference type
std::is_same_v<decltype((foo)), const int*&>

// + slideshow={"slide_type": "subslide"}
// Back to arrays: You can declare functions with array type
int first(int ia[]) { return ia[0]; }

// +
// But they will also accept pointers as arguments:
int i{123};
int* pi{&i};

first(pi)

// + slideshow={"slide_type": "-"}
std::is_same_v<decltype(first), int(int[])>
// -

std::is_same_v<decltype(first), int(int*)>

std::is_same_v<int(int[]), int(int*)>

// + slideshow={"slide_type": "-"}
std::is_same_v<int(int(&)[]), int(int*&)>

// + slideshow={"slide_type": "subslide"}
int foo(int (&x)[5]) { return x[0]; }
// -

int bar(int (&x)[]) { return x[0]; }

int baz(int* const& x) { return x[0]; }

int ia[]{1, 2, 3, 4, 5};
foo(ia)

// +
// Nope.
// bar(ia)
// -

std::is_same_v<decltype(bar), int(int(&)[])>

baz(ia)

// + [markdown] slideshow={"slide_type": "subslide"}
// From [cppreference.com](https://en.cppreference.com/w/cpp/language/function):
//
// The type of each function parameter in the parameter list is determined according to the following rules:
//
// - \[...\]
// - If the type is "array of T" or "array of unknown bound of T", it is replaced by the type "pointer to T"
// - If the type is a function type F, it is replaced by the type "pointer to F"
// - \[...\]

// + slideshow={"slide_type": "subslide"}
int ia[]{1, 2, 3, 4, 5};
ia[1]
// -

&(ia[0])

ia + 0

// + slideshow={"slide_type": "-"}
ia[2]

// + slideshow={"slide_type": "-"}
*(ia + 2)
// -

// (This is how the built-in index operator is defined.)

// + [markdown] slideshow={"slide_type": "subslide"}
// Of course, according to the definition, it's perfectly legal to write...
// -

2[ia]

// ... that's just common sense, right?

// + [markdown] slideshow={"slide_type": "slide"}
// ## Back to Pointers...
// -

// ### Code Examples
//
// - `pointers/pointers.hpp`
// - `pointers/shapes.hpp`
// - `pointers/array_danger.hpp`

// + [markdown] slideshow={"slide_type": "slide"}
// ## TTT: Board
//
// - Allow users to iterate over `Board` instances
// - Make the class `Board` usable by STL algorithms

// + [markdown] slideshow={"slide_type": "slide"}
//
// ## Ranges: Iterable Types
//
// - It is often useful to make types iterable, in particular more utility-focused types
// - For this types need to provide only `begin()` and `end()` member functions
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
// -

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
// ```
// for (const int i : IntRangeV0{10, 20}) {
//     std::cout << i << "\n";
// }
// ```
// prints the numbers 10 to 20 on `std::cout`. To achieve this, store all numbers between `min` and `max` in a vector insided the `IntRange` instance.
//
// Test your implementation using Catch2.
//
// *Note:* You can use the project `workshops/starter_kit_100/` to implement your solution.

// + [markdown] slideshow={"slide_type": "slide"}
// ## STL Algorithms
//
// The STL provides many generic algorithms that can be used with any type that satisfies the `range` concept.
// -

// ### Mini-Workshop: Sum of Integers
//
// Write a function `int sum_from_to(int min, int max)` that computes the sum of all numbers from `min` to `max` (inclusive). Use an `IntRangeV0` and an appropriate algorithm from the STL to perform the task.

// + [markdown] slideshow={"slide_type": "slide"}
// ## Lambdas

// + [markdown] slideshow={"slide_type": "slide"}
// ## Iterator Categories

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
// ## Lambdas: Captures

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


