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
// # Advanced C++: Introduction

// + [markdown] slideshow={"slide_type": "slide"}
// ## Contents (Part 1)
//
// - Functions, lambdas, compile-time programming
// - Memory management, move semantics, smart pointers
// - Construction, destruction, initialization, RAII
// - Object oriented programming, classes, inheritance, polymorphism
// - Handling errors: exceptions and alternatives

// + [markdown] slideshow={"slide_type": "subslide"}
// ## Contents (Part 2)
//
// - STL: templates, algorithms, generic programming
// - Template metaprogramming: type traits, SFINAE, etc.
// - Modern template metaprogramming: concepts
// - Concurrency

// + [markdown] slideshow={"slide_type": "subslide"}
// ## Question Time
//
// - What do you expect from this course?
// - How familiar are you with the topics?

// + [markdown] slideshow={"slide_type": "slide"}
// ## Course Materials
//
// - GitHub repositories:
//     - [Course materials](https://github.com/hoelzl/AdvancedCpp)
//     - [Reviser example](https://github.com/hoelzl/Reviser)

// + [markdown] slideshow={"slide_type": "slide"}
// # `https://github.com/hoelzl/AdvancedCpp`
// -

// ## Recommended Software Environment
//
// - Visual Studio 2022 (Windows) or Clang &geq; 10, for very few examples Clang &geq; 14
// - CMake &geq; 3.21 (Older

// + [markdown] slideshow={"slide_type": "slide"}
// ## And now...
// -

#include <iostream>
std::cout << "Let's get this show on the road!\n";
