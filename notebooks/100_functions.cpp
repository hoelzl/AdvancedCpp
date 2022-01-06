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

// # Functions and Lambdas

// ## First Example: Tic Tac Toe
//
// Let's implement the game of tic-tac-toe in a procedural manner.
//
// We'll "overengineer" this solution to show off more features of C++.

// ## TTT: Field and Board
//
// - Define a scoped enumeration `FieldValue` representing the value of a field on the board
// - Define a class `Board` containing an array of 9 fields
// - Make the class `Board` usable by STL algorithms

// ## Interlude Catch2
//
// In order to get working software we need to write tests as we build the system. In this course we use the [Catch2](https://github.com/catchorg/Catch2) framework for writing tests.
//
// TODO: Intro to Catch2

// ## Type Aliases

// ## Range-based For Loop
//
// Why can we simply loop over our `Board`?
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

// ## STL Algorithms

// ## Lambdas

// ## Iterator Categories

// ## Ranges

// ## Using Tools: Address Sanitizer

// ## TTT: Extend the Board
//
// - Define a function `field_value(Position pos)` that retrieves the field at a given position
// - There are various ways to model positions, we'll use a `std::pair<short, short>` for now
// - Write tests that test the new functionality

// ## Static Variables

//

// ## TTT: Valid Moves
//
// - Define a member function `Board::is_move_valid(Position pos)` that checks whether `pos` is empty
// - Define a member function `Board::valid_moves()` that returns a set of all valid moves.

// ## Lambdas: Captures
