#include "rpg_dice.hpp"

#include "catch2/catch_test_macros.hpp"

using namespace dice;

TEST_CASE("class ConstantDie")
{
    constexpr auto a_random_number = 3;

    auto die = ConstantDie{a_random_number};

    SECTION("roll() always rolls the same number.")
    {
        CHECK(die.roll() == a_random_number);
        CHECK(die.roll() == a_random_number);
    }

    SECTION("min() and max() are the same number.")
    {
        CHECK(die.min() == a_random_number);
        CHECK(die.max() == a_random_number);
    }
}

TEST_CASE("Single fair six-sided die")
{
    auto die = FairDice{1, 6, 42};

    SECTION("roll() rolls the expected results.")
    {
        // These results should be deterministic, given that we are using a Mersenne
        // Twister with fixed parameters and seed.
        CHECK(die.roll() == 1);
        CHECK(die.roll() == 6);
        CHECK(die.roll() == 5);
    }

    SECTION("min() and max() are correct.")
    {
        CHECK(die.min() == 1);
        CHECK(die.max() == 6);
    }
}

TEST_CASE("Two fair six-sided dice")
{
    auto die = FairDice{2, 6, 42};

    SECTION("roll() rolls the expected results.")
    {
        CHECK(die.roll() == 7);
        CHECK(die.roll() == 10);
        CHECK(die.roll() == 7);
    }

    SECTION("min() and max() are correct.")
    {
        CHECK(die.min() == 2);
        CHECK(die.max() == 12);
    }
}

TEST_CASE("Three fair 20-sided dice")
{
    auto die = FairDice{3, 20, 101};

    SECTION("roll() rolls the expected results.")
    {
        CHECK(die.roll() == 30);
        CHECK(die.roll() == 27);
        CHECK(die.roll() == 34);
    }

    SECTION("min() and max() are correct.")
    {
        CHECK(die.min() == 3);
        CHECK(die.max() == 60);
    }
}

TEST_CASE("FairDie rolls are between min() and max()", "[.][excessive]")
{
    constexpr auto num_tests = 10'000;
    auto die = FairDice{5, 12, 42};

    for (auto i = 0; i != num_tests; ++i) {
        auto const value = die.roll();
        CHECK(die.min() <= value);
        CHECK(value <= die.max());
    }
}

TEST_CASE("Empty SumDice.")
{
    auto die = SumDice();

    SECTION("roll() rolls nothing.")
    {
        CHECK(die.roll() == 0);
        CHECK(die.roll() == 0);
        CHECK(die.roll() == 0);
    }

    SECTION("min() and max() are correct.")
    {
        CHECK(die.min() == 0);
        CHECK(die.max() == 0);
    }
}

TEST_CASE("Sum of two 6-sided dice.")
{

    auto die = SumDice();
    die.add_die(FairDice{1, 6, 42});
    die.add_die(FairDice{1, 6, 44});


    SECTION("roll() rolls the expected results.")
    {
        CHECK(die.roll() == 6);
        CHECK(die.roll() == 12);
        CHECK(die.roll() == 7);
    }

    SECTION("min() and max() are correct.")
    {
        CHECK(die.min() == 2);
        CHECK(die.max() == 12);
    }
}

TEST_CASE("Sum of two 6-sided dice, added via add_dice().")
{

    auto die = SumDice();
    die.add_dice(FairDice{1, 6, 42}, FairDice{1, 6, 44});


    SECTION("roll() rolls the expected results.")
    {
        CHECK(die.roll() == 6);
        CHECK(die.roll() == 12);
        CHECK(die.roll() == 7);
    }

    SECTION("min() and max() are correct.")
    {
        CHECK(die.min() == 2);
        CHECK(die.max() == 12);
    }
}

TEST_CASE("Sum of two 6-sided dice, added via constructor.")
{
    auto die = SumDice(FairDice{1, 6, 42}, FairDice{1, 6, 44});

    SECTION("roll() rolls the expected results.")
    {
        CHECK(die.roll() == 6);
        CHECK(die.roll() == 12);
        CHECK(die.roll() == 7);
    }

    SECTION("min() and max() are correct.")
    {
        CHECK(die.min() == 2);
        CHECK(die.max() == 12);
    }
}

TEST_CASE("Single simple six-sided die")
{
    auto die = SimpleDie{6, 42};

    SECTION("roll() rolls the expected results.")
    {
        // These results should match the six-sided FairDice instance with one die.
        CHECK(die.roll() == 1);
        CHECK(die.roll() == 6);
        CHECK(die.roll() == 5);
    }

    SECTION("min() and max() are correct.")
    {
        CHECK(die.min() == 1);
        CHECK(die.max() == 6);
    }
}


TEST_CASE("Sum of two simple six-sided dice.")
{
    auto die = SumDice{SimpleDie{6, 42}, SimpleDie{6, 44}};

    SECTION("roll() rolls the expected results.")
    {
        // This does not have to match the FairDice{2, 6, 42} instance, since we use two
        // RNGs instead of one, so the sequences of random numbers are different. But it
        // should match the sum of fair dice.
        CHECK(die.roll() == 6);
        CHECK(die.roll() == 12);
        CHECK(die.roll() == 7);
    }

    SECTION("min() and max() are correct.")
    {
        CHECK(die.min() == 2);
        CHECK(die.max() == 12);
    }
}


TEST_CASE("Multiple roll of a 6-sided die.")
{
    auto die = MultiRollDie{2, SimpleDie{6, 42}};

    SECTION("roll() rolls the expected results.")
    {
        // This should again match the FairDice{2, 6, 42}.
        CHECK(die.roll() == 7);
        CHECK(die.roll() == 10);
        CHECK(die.roll() == 7);
    }

    SECTION("min() and max() are correct.")
    {
        CHECK(die.min() == 2);
        CHECK(die.max() == 12);
    }
}
