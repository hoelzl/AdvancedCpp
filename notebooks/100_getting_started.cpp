// -*- coding: utf-8 -*-
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
// (*) In cases where you need a fixed-size storage. If you need variable size storage `std::vector` is almost always superior to both.

// + [markdown] slideshow={"slide_type": "slide"}
// ## The [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
//
// The [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) are a set of rules/guidance that help writing more reliable and usable C++ code.
//
// They are *really good.*
//
// Read them! Use them!
// -

// ### Guidelines
//
// - [SL.con.1: Prefer using STL array or vector instead of a C array](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rsl-arrays)

// + [markdown] slideshow={"slide_type": "slide"}
// ### Types, Objects, Values, Variables
//
// - A *type* restrict the operations for an entity and provides semantic meaning to its sequence of bits ([details](https://en.cppreference.com/w/cpp/language/type))
//     - Fundamental/compound
//         - fundamental: `void`, `int`, `double`, `bool`, ...
//         - compound: reference, pointer, array, class, ...
//     - Complete/incomplete; `void`, `foo[]`, forward declarations are incomplete
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

// + [markdown] slideshow={"slide_type": "subslide"}
// ### Some Caveats
//
// - Pointers have no influence on the lifetime of an object; there is no way to check whether the pointed-to object is still alive
// - Pointers can be compared, but comparison with `<` is only defined for pointers to the same object
// - `std::less` guarantees a strict total order for arbitrary pointers. (Note that `std::less` is a class that must be instantiated)

// + slideshow={"slide_type": "-"}
#include <functional>
int i{2}, j{1};
// &i < &j // Probably works, but no guarantees
std::less{}(&i, &j)

// + slideshow={"slide_type": "-"}
int ia[5]{};
ia < &ia[3] // OK

// + [markdown] slideshow={"slide_type": "subslide"}
// ### Syntax

// + slideshow={"slide_type": "subslide"}
int* foo;                     // pointer to int
int** bar;                    // pointer to pointer to int
const int* baz;               // pointer to const int
int const* baz2;              // pointer to const int (same as above)
int *const quux = nullptr;    // const pointer to int
const int *const p = nullptr; // const pointer ot const int
// -

int i;
int& ri{i};              // (lvalue) reference to int
int*& rpi{foo};          // (lvalue) reference to pointer to int
// int&* pri             // ERROR: pointer to reference to int
int (*f)(double);        // pointer to a function taking a double, returning an int
int *g(double);          // function taking a double returning a pointer to int

// + slideshow={"slide_type": "subslide"}
int ai[3];                // array of int
int aai[3][4];            // "two-dimensional" array (array of array of int)
int* api[4];              // array of pointer to int
int (*pai)[];             // pointer to array of int (of unspecified size)
int (&rai)[3]{ai};        // reference to array of int
// int& ari[3];           // ERROR: Array of references to int

// +
struct Widget{
    int foo(int j) { return j + 2; }
};

int (Widget::*pmw)(int);  // pointer to member function
Widget w{};
int (Widget::*pmw2)(int){&Widget::foo};
(w.*pmw2)(1)
// -

Widget* pw{&w};
(pw->*pmw2)(5)

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
#include <type_traits>
std::is_same<decltype(pi2), int[]>::value
// -

std::is_same_v<decltype(pi2), int*>

std::is_same_v<std::decay_t<int[]>, int*>

// + slideshow={"slide_type": "-"}
#include <type_traits>
int ia[]{1, 2, 3, 4, 5};
auto pi2{ia};
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

int i{2};
i[ia]

// ... or even ..

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

// ### Guidelines
//
// - [I.13: Do not pass an array as a single pointer](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#i13-do-not-pass-an-array-as-a-single-pointer)
// - [F.22: Use `T*` or `owner<T*>` to designate a single object](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rf-ptr)
// - [SL.str.4: Use `char*` to refer to a single character](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rstr-char*)
// - [ES.62: Don’t compare pointers into different arrays](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Res-arr2)

// ### Summary of Relevant Guidelines
//
// - [SL.con.1: Prefer using STL array or vector instead of a C array](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rsl-arrays)
// - [I.13: Do not pass an array as a single pointer](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#i13-do-not-pass-an-array-as-a-single-pointer)
// - [F.22: Use `T*` or `owner<T*>` to designate a single object](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rf-ptr)
// - [SL.str.4: Use `char*` to refer to a single character](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rstr-char*)
// - [F.23: Use a `not_null<T>` to indicate that “null” is not a valid value](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rf-nullptr)
// - [F.24: Use a `span<T>` or a `span_p<T>` to designate a half-open sequence](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rf-range)
// - [F.25: Use a `zstring` or a `not_null<zstring>` to designate a C-style string](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rf-zstring)
// - [F.42: Return a `T*` to indicate a position (only)](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rf-return-ptr)
// - [F.43: Never (directly or indirectly) return a pointer or a reference to a local object](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rf-dangle)
// - [R.3: A raw pointer (a `T*`) is non-owning](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rr-ptr)
// - [ES.62: Don’t compare pointers into different arrays](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Res-arr2)
// - [ES.65: Don’t dereference an invalid pointer](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Res-deref)
// - [SL.str.11: Use `gsl::span<char>` rather than `std::string_view` when you need to mutate a string](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rstr-span)
