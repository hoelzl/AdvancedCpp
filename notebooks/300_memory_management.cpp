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

// # Memory Management and Resource Handling

// + [markdown] slideshow={"slide_type": "slide"}
// ## Using Tools: Address Sanitizer
// -

// ## References
//
// - A reference is an alias for an existing name
// - References are not objects themselves
//     - They denote the object with which they were initialized
// - Using a reference is the same as using the original object
//     - Taking the address returns the original object
//     - Changing the reference changes the original object
// - References are not just "syntactic sugar" for pointers
//
// ```c++
// Widget w{};
// Widget& rw{w};
// ...
// &w == &rw; // Always true
// ```

// ## Using Tools: Address Sanitizer


