# RPG Dice

In role-playing games decisions involving measure of randomness, such as fights
between players and NPCs, are often resolved by rolling dice. Many role-playing
systems use not only the well-known six-sided dice, but also 4-sided, 12-sided
or 20-sided dice. Often multiple dice, either of the same kind or of different
kinds are rolled together.

The number and kind of dice is specified using the following notations:

```text
<number of dice> d <faces per die>
```

For example, rolling two six-sided dice can be written down as `2d62. More
complex combinations of dice are written as sums. `3d20 + 2d6 + 4` means "roll
three 20-sided dice, two 6-sided dice and add 4 to the result".

In this exercise, we want to develop a library that can represent these kinds of
dice rolls. To allow easy customization we want to build this as a hierarchy of
different kinds of dice sharing a common interface.

Write appropriate tests for the implementation of every class. Have fun!

## The Interface: `Dice`

Define an abstract class `Dice` with a virtual destructor and methods

```c++
virtual int roll() = 0;
virtual int min() const = 0;
virtual int max() const = 0;
```

Take into account the Rule of Five.

## Simple Dice

### Constan Die

Implement a class `ConstantDie` that always rolls a constant result (specified at construction time) and implements the `Dice` interface.

### Absract Class for Uniform Random Dice

Most dice need a source of random numbers. We can centralize this in another
abstract class `UniformRandomDice` that inherits from dice and provides a protected
methods

```c++
int random_int()
```

that returns a random number. (You might want to implement helper methods that
allow clients to access the random engine and the random distribution, but this
is not required.)

### Fair Dice

Implement a class `UniformRandomDice` that simulates rolling a fixed number `n` of `d`-sided dice (or, equivalently rolling a single `d`-sided die `n` times).

## Compound Dice

### Sum Dice

Implement a class `SumDice` that simulates rolling a given set of dice (passed
in at construction time) one time. Optionally add a method `add_dice` that allows the addition of dice after the `SumDie` instance has been constructed.

### Simple Die and Multi Roll Die

We could split the functionality of the class `UniformRandomDice` (that
implements simultaneous rolling of multiple dice) into two simpler classes:
`SimpleDie` that rolls a single die once, and `MultiRollDie` that takes another
die and rolls it a given number of times.

Implement these two classes.