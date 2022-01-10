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

// # Generic Programming

// ## Templates
//
// - Most code in C++ must be written for a specific type
//     - A lot of code is structurally similar (e.g., sorting)
//     - We don't want to write this over and over again
// - Polymorphism (object-orientation)
//     - Code that works for classes related by inheritance
//     - Implementation to use chosen at *runtime*
// - Allow us to write code that works for arbitrary types
//     - As long as they support the required functionality
//     - E.g., can sort anything, as long as `operator<` is available
//     - In C++20 this is formalized by *concepts*
//     - Implementation is chosen at *compile time*

// ### Practical Aspects
//
// - The compiler has to see the body of the template when it is *instantiated* for a new type
// - Therefore templates are typically defined in header files
// - This can be done without specifying `inline`

// ## Function Templates
//
// See `lectures/compile_time_eval/function_templates.hpp`.

// ## Class Templates
//
// See `lectures/compile_time_eval/class_templates.hpp`.

// ## Nontype Template Parameters
//
// See `lectures/compile_time_eval/nontype_templates.hpp`
