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

// # The Standard Template Library

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




