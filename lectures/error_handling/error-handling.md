# Error Handling Strategies in C++

We have several different strategies to deal with errors in C++

- Throwing and catching exceptions in various forms:
  - With `throw` and `try`/`catch`.
  - Throwing but not catching exceptions (except maybe at the system/subsystem
    level).
  - Using deterministic exceptions according to Herb Sutter's proposal
    "Zero-overhead deterministic exceptions: Throwing values"
    [link](http://open-std.org/JTC1/SC22/WG21/docs/papers/2018/p0709r0.pdf).
    (These are neither part of standard C++ nor implemented in any compiler
    AFAICT but I'm mentioning them since they seem to embody many of the
    characteristics an solution for embedded systems ought to provide). Note
    that there are a number of competing proposals, in particular Emil
    Dotchevski's proposal "Zero-Overhead Deterministic Exceptions: Catching
    Values"
    [link](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2021/p2232r0.html)
    looks quite promising.
- Establishing a global or thread-local status variable (possible per subsystem)
  and either:
  - Returning a result from functions that indicates whether the status code
    represents a valid error state.
  - Having a "no error" status code and checking the value of the global status
    variable for errors. This frees the return value of the function for its
    usual function of returning the function's result.
- Moving error cases into the type system.

The following discussion about advantages/disadvantages of different solutions
is independent of any application domain, but different domains will obviously
assign different weights to the various trade-offs.

## Exceptions

### Throwing and catching exceptions

See `examples/try-catch`.

#### Advantages of exceptions:

- Separate error handling from normal control flow.
  - Clearly describe "happy path" of code execution.
  - Remove branches from "happy path" thus enabling better optimizations.
- Allow one-phase construction of objects.
- Do not restrict on use of STL, operators, etc.
- Do not restrict use of third-party libraries.
- Error handling cannot be forgotten (exceptions will unwind the whole stack if
  they are not caught).
- *Well-implemented exception handling* allows program to recover from certain
  errors.
- Remapping exceptions between application layers is relatively easy.

#### Disadvantages of exceptions:

- Code needs to provide exception guarantees to allow meaningful handling of
  exceptions.
- Some exception implementations increase program size. (Particularly
  table-based aka. zero-cost exceptions.)
- Since catch clauses can throw, exceptions need to potentially allocate
  unbounded amount of storage dynamically.
- Care has to be taken to provide appropriate exception guarantees in every
  function, even in ones not visibly involved in the exception flow.
- Upper time limit for handling exceptions is difficult to establish.
  - Work for unwinding the stack depends on the stack depth, therefore difficult
    to establish statically.
  - Exceptions are implicitly type erased (by the program runtime), some sort of
    RTTI is needed to figure out the exception type, although only a (simple)
    subset of RTTI.
- Exceptions slow down certain execution paths of the program; for the commonly
  used exception implementation (zero-cost exceptions) the costs are
  - Slow execution of exception paths (some authors say up to 60 times slower)
    due to the need to unwind the stack and find catch blocks.
  - Eliminated opportunities for compiler optimizations in the happy path.

### Throwing but not catching exceptions

See `examples/throw-only`.

This solution uses exceptions essentially as an alternative to `std::terminate`
for the production system, but offers better facilities for debugging during
development. It offers most of the advantages of exceptions (except remapping
and error recovery) and eliminates some of the disadvantages:

#### Advantages (relative to standard exceptions)

- Less stringent exception guarantees needed than for exceptions which are
  caught. But resources that are not automatically reclaimed by the OS, such as
  files, etc. still need to be properly handled in the case of unwinding.
- Only a single exception can be in flight since it is never caught.

#### Disadvantages (relative to standard exceptions)

- Recovery from errors is not possible.
- Remapping exceptions between application layers is not possible.

### Deterministic exceptions (proposal)

(No example.)

Solves most of the problems with exceptions. Biggest downside: it's not yet available.

Some of the advantages of this proposal might be achieved by restricting the
allowed uses of exceptions (e.g., no throwing from `catch` clauses) and
modifying the C++ runtime library (i.e., having a custom
`__cxa_allocate_exception` that allocates exceptions from a pre-allocated buffer
and terminates the program if an exception is thrown that does not fit into the
pre-allocated buffer).

### Considerations in a real-time/safety-critical context.

The non-determinism introduced by (traditional) C++ exceptions can be
problematic for real-time or safety-critical applications. Particular
consideration should be given to the following Rules from the Adaptive Autosar
C++14 Guidelines:

- *Rule A15-0-6* (required, verification / toolchain, non-automated): An
  analysis shall be performed to analyze the failure modes of exception
  handling. In particular, the following failure modes shall be analyzed: (a)
  worst time execution time not existing or cannot be determined, (b) stack not
  correctly unwound, (c) exception not thrown, other exception thrown, wrong
  catch activated, (d) memory not available while exception handling.

- *Rule A15-0-7* (required, verification / toolchain, partially automated):
  Exception handling mechanism shall guarantee a deterministic worst-case time
  execution time.

- *Rule A15-0-8* (required, verification / toolchain, non-automated): A
  worst-case execution time (WCET) analysis shall be performed to determine
  maximum execution time constraints of the software, covering in particular the
  exceptions processing.

Note that Rule A15-0-8 seems to indicate that a WCET analysis is required
*whether exceptions are used or not*.

## Error handling by local or global error status

### Status value plus global error handler: `errno`

See `examples/global-error-code`

The usual convention for this kind of error handling is for functions to return
a status indicator and store an error code in a global (or, since C++11,
thread-local) variable.

#### Advantages

- Control flow for the error case is visible together with normal program flow.
  (May also be considered a disadvantage.)
- Return channel may be used to pass result back to caller, if the return type
  of the function can express all desired values plus an error value (e.g.,
  `NaN` for doubles).
- Good interoperability with C code.

#### Disadvantages

- Incompatible with some STL functions.
- No separation of success- and error-control flow: code for handling errors has
  to be scattered throughout the program.
- Function results may need to be returned in output arguments if no obvious
  encoding for an error value exists in the result type (e.g., for functions
  that can return any `int` value).
- Two-phase construction is necessary for objects whose initialization can fail.
  This weakens invariants.
- Cannot use operators.
- A custom scheme for freeing allocated resources in the error case must be
  determined.
- All functions/methods that can produce errors are impure; violates
  command/query separation.
- Easy to forget/defer Error handling. This can be mitigated by using
  `nodiscard` annotations.
- Output parameters lead to objects in invalid/uninitialized states, reduced
  optimization possibilities.
- Functions cannot be nested to use their return value; value passing becomes
  explicit via local variables.

### Returning error codes as return value

See `examples/error-code-with-query`.

An integral value representing the error that occurred is returned by a function
that can fail. Advantages and disadvantages are similarly to status value plus
global error handler.

#### Advantages (relative to global error handler)

- No global state is necessary for error handling.
- No memory allocation or type erasure is needed for error handling path.
- Error case is very efficient since it uses the highly optimized return-value
  path.
- Remapping error codes between application layers is relatively easy.

#### Disadvantages (relative to global error handler)

- Error codes defined by different modules may overlap, potentially obscuring
  the program part that caused the error. This can be avoided by using, e.g.,
  scoped enumerations instead of integral values. (Using dedicated error types
  poses some other problems, e.g., by violating the "Open/closed principle").

### Returning error codes by output parameter

No example, I'm not a Fortran programmer.

#### Advantages

- Error location needs to be passed as parameter, thus making it more difficult
  to completely ignore the error.

#### Disadvantages

- Location for error code has to be passed to function, making for clumsy
  function interfaces.

### Using `std::error_code`

No example; would probably be similar to `examples/error-code-with-query`.

Stores an integer value and a pointer to a `domain` representing the library where the error occurred.

- Similar to "returning error codes as return value".

## Returning a union of value and error

This solution is a kind of compromise between throwing exceptions and returning
status codes. Existing implementations of this scheme are, e.g., the proposed `std::expected` and `boost::outcome`.

### Returning value and error via `std::expected`

See `examples/types-expected`.

Instead of returning a simple error code, the function's return type is a sum of
the return type and an error type. The interface of `std::expected` is optimized
for the "happy path".

#### Advantages

- Error handling is not easily forgotten *for functions that return a value*.
  Error handling for functions without result can be "enforced" by using
  `[[nodiscard]]` annotations.
- Return channel may be used to pass values back to the caller (although
  possibly slightly less efficiently since the return type lifted into the error
  domain is typically larger than the pure return type).
- May allow the program to recover from certain errors.
- Remapping errors between application layers is relatively easy.
- Control flow for the error case is visible together with normal program flow.
  (May also be considered a disadvantage.)

#### Disadvantages

- No separation of success and error control flow: code for handling errors has
  to be scattered throughout the program.
- A custom scheme for freeing allocated resources in the error case must be
  determined.
- Easy to forget/defer Error handling *for commands* unless `nodiscard`
  annotations are used consistently.
- If not used with exceptions as backup mechanism:
  - Incompatible with some STL functions.
  - Cannot use operators if the operation may fail.
  - Two-phase construction is necessary for objects whose initialization can
    fail. This weakens invariants.
