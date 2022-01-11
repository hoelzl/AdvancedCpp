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
// # Memory Management and Resource Handling

// + [markdown] slideshow={"slide_type": "slide"}
// ## Move Construction/Assignment
//
// - Many types in C++ are *resource handles*: they have a small stack-allocated header and manage potentially large amounts of heap space.
//     - Example: STL collections, strings, ...
// - Copying the header is cheap, copying the resources is often very expensive

// + [markdown] slideshow={"slide_type": "subslide"}
// ![Missing Image?](img/handles.png)

// + [markdown] slideshow={"slide_type": "slide"}
// - Value semantics (for fuction calls and variable assignments) requires us to copy everything
//     - Otherwise modifications would be visible in other objects

// + [markdown] slideshow={"slide_type": "subslide"}
// ![Missing Image?](img/copy_01.drawio.png)

// + [markdown] slideshow={"slide_type": "subslide"}
// ![Missing Image?](img/copy_02.drawio.png)

// + [markdown] slideshow={"slide_type": "subslide"}
// ![Missing Image?](img/copy_03.drawio.png)

// + [markdown] slideshow={"slide_type": "slide"}
// - The cost of copying objects is why we often pass by reference/pointer
//     - But that brings problems with lifetime management
//     - And it makes compiler optimizations more difficult
// - However: if we knew that an object was no longer needed after being copied, we could just create a new header and steal the (expensive) resources from the old object

// + [markdown] slideshow={"slide_type": "subslide"}
// ![Missing Image?](img/move_01.drawio.png)

// + [markdown] slideshow={"slide_type": "subslide"}
// ![Missing Image?](img/move_02.drawio.png)

// + [markdown] slideshow={"slide_type": "slide"}
// - "Stealing resources" is what move constructors and assignment operators do
// - The only trick is to identify when we can do this

// + [markdown] slideshow={"slide_type": "slide"}
// ## References
//
// - A reference is an alias for an existing name
// - We say a reference *binds to* a variable if it is initialized with that variable
// - There exists lvalue (`&`) and rvalue (`&&`) references
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

// + slideshow={"slide_type": "subslide"}
#import <type_traits>
std::is_object_v<int&>
// -

std::is_object_v<int&&>

std::is_object_v<int*>

// + [markdown] slideshow={"slide_type": "slide"}
// ## Value Categories (Rvalues and Lvalues)
//
// - The distinction between rvalues and lvalues is crucial for move semantics and for template metaprogramming
// - Each expression in C++ has exactly one of three *primary value categories*:
//     - prvalue
//     - xvalue
//     - lvalue
// - To define these categories it is easier to start differently:

// + [markdown] slideshow={"slide_type": "-"}
// An expression is a
// - *glvalue* (generalized lvalues): if its evaluation determines the identity of an object (or function)
// - *prvalue* (pure rvalue): if it either
//     - computes the value of an operand or built-in operator (no result object)
//     - initializes an object (has a *result object*; often a temporary)
// - *xvalue* (expiring value): if it is a glvalue whose resources can be reused
// - *lvalue*: if it is a glvalue that is not an xvalue
// - *rvalue*: if it is a prvalue or an xvalue

// + [markdown] slideshow={"slide_type": "subslide"}
// - Note that *expressions* have value categories; *variable declarations do not have value categories!*
// - The type of a variable with reference type determines *to which objects it can bind* not which value category it has when it occurs in an expression
// - In particular, the expression consisting of the variable's name is *always an lvalue*, therefore we often have "lvalues of type rvalue reference"!

// + [markdown] slideshow={"slide_type": "subslide"}
// ### Properties of Glvalues:
//
// - May be implicitly converted to a prvalue
// - May be polymorphic
// - May have incomplete type
//
// ### Properties of Lvalues
//
// - Same as glvalues
// - Address may be taken (`&++i`)
// - May be used on left hand side of assignments (if modifiable)
// - May be used to initialize an lvalue reference

// + [markdown] slideshow={"slide_type": "subslide"}
// ### Properties of Rvalues
//
// - Address cannot be taken
// - Can't be used as left-hand side of assignment (usually)
// - May be used to initialize a const lvalue reference or rvalue reference in which case the lifetime of the object identified by the rvalue is *extended until the scope of the reference ends*.
// - Binds to rvalue reference overloads during overload resolution (i.e., the move constructor is selected.)
// -

// ### Some properties, again
//
// - All rvalues, i.e., prvalues and xvalues bind to rvalue references
// - All glvalues, i.e., lvalues and xvalues may be polymorphic

// + [markdown] slideshow={"slide_type": "subslide"}
// ### Lvalues (examples)
// - The name of a variable, function, template parametr object, data member *regardless of type*
// - A function call whose return type is lvalue reference (`std::cout << 1`)
// - Built-in assignment and compound assignment expressions (`x = 1`, `x += 3`)
// - Built-in pre-increment and decrement (`++a`), indirection (`*p`), subscript (`a[n]`) (if one operand is an lvalue)
// - `a.m`, `a->m`, `a.*m`, `a->*m` most of the time
// - `a ? b : c` sometimes
// - a string literal
// - a cast expression to lvalue type (`static_cast<int&>(x)`)
// - a function call whose return type is rvalue reference to function or a cast to rvalue reference to function

// + [markdown] slideshow={"slide_type": "subslide"}
// ### Prvalues (examples)
//
// - A literal (except for string literals) (`42`)
// - A function call whose return type is non-reference (`vec.empty()`)
// - Built-in arithmetic, logical, comparison expressions
// - Address of expression (`&a`)
// - `a.m`, `a->m`, `a.*m`, `a->*m` if `m` is member enumerator or non-static member function
// - `a ? b : c` sometimes
// - A cast to non-reference type
// - The `this` pointer
// - A lambda expression

// + [markdown] slideshow={"slide_type": "subslide"}
// ### Xvalues (examples)
//
// - A function call or overloaded operator expression whose return type is rvalue reference to object (`std::move(x)`)
// - A cast expression to rvalue reference type (`static_cast<int&&>(x)`)
// - `a.m`, `a->m`, `a.*m` sometimes
// - Any expression that designates a temporary object after temporary materialization

// + [markdown] slideshow={"slide_type": "slide"}
// ## Construction, Destruction, Copy, and Move
//
// See `lectures/memory_and_polymorphism`, in particular projects `pam_simple`, `pam_memory`, and `pam_copy_move`.
// -

// ## Using Tools: Address Sanitizer


