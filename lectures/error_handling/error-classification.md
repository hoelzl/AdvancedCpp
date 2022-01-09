# Error Classification

Following Herb Sutter's proposal [Zero-overhead deterministic exceptions:
Throwing
values](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p0709r0.pdf) and
the Autosar guidelines for C++14, we classify errors into five classes:

- Corruption of the abstract machine (e.g., stack overflow)
- Nonrecoverable error (e.g., precondition violation)
- Heap exhaustion
- Recoverable error (e.g., file not found)
- Alternate success (e.g., return first kB of network stream)

Nonrecoverable and recoverable errors correspond to the concepts of unchecked
and checked exceptions in the Autosar guidelines.

When the abstract machine is corrupted or a nonrecoverable error occurs the only
recovery strategy is to terminate the program; in practical terms the same is
typically true for heap exhaustion.

When following the Autosar guidelines, error handling is only permissible for
recoverable errors, since using exceptions for alternate successes is forbidden
by Rule A 15-0-1.

Which errors count as nonrecoverable and which ones as recoverable errors
depends to a large degree on the specification of contracts we use (i.e., the
pre- and postconditions and the invariants). (See e.g., [The Use and
Implementation of
Contracts](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/p0147r0.html).)

A function with a *wide contract* may be called with all (type-correct) inputs;
it guarantees to do something appropriate with any input it receives. A function
with a *narrow contract* specifies the preconditions it requires to work (and
the postconditions it guarantees after completion). It is an (unrecoverable)
program error to call a function with narrow contract with arguments that do not
satisfy its preconditions.  For example `SqrtWide` has a wide contract and may
be called with any double value, even negative value. Its specification
therefore has to define its behavior when called with negative arguments (e.g.,
return `Nan`, return the square root for the absolute value of its argument,
throw an exception, etc.).

```
double SqrtWide(double arg);
```

The function `SqrtNarrow` has a narrow contract. It is a (nonrecoverable)
program error to call it with a negative argument:

```
double SqrtNarrow(double arg)[[expects: arg >= 0]];
```

Choosing whether to use wide or narrow contracts has significant impact on the
structure of the program and on the viability of various error handling
strategies.