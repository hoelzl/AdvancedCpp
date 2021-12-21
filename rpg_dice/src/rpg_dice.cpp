#include "rpg_dice.hpp"

#include <algorithm>
#include <iterator>
#include <ranges>

using std::begin, std::end;
using std::views::iota;

namespace dice {

ConstantDie::ConstantDie(int value) : value_{value} {}

int ConstantDie::roll() { return value_; }

int ConstantDie::min() const { return value_; }

int ConstantDie::max() const { return value_; }

RandomDice::RandomDice(seed_type seed) { engine_.seed(seed); }

int FairDice::roll()
{
    auto rolls = iota(0, num_rolls_);
    return std::accumulate(begin(rolls), end(rolls), 0, [this](int val, auto) {
        return val + random_int();
    });
}

int FairDice::min() const
{
    // We roll at least 1 in every roll.
    return num_rolls_;
}

int FairDice::max() const { return num_rolls_ * num_sides_; }


int SumDice::roll()
{
    return accumulate_dice([](int val, auto& die) { return val + die->roll(); });
}

int SumDice::min() const
{
    return accumulate_dice([](int val, auto& die) { return val + die->min(); });
}

int SumDice::max() const
{
    return accumulate_dice([](int val, auto& die) { return val + die->max(); });
}

int SimpleDie::roll() { return random_int(); }

int SimpleDie::min() const { return 1; }

int SimpleDie::max() const { return num_sides_; }

int MultiRollDie::roll()
{
    auto rolls = iota(0, num_rolls_);
    return std::accumulate(begin(rolls), end(rolls), 0, [this](int val, auto) {
        return val + die_->roll();
    });
}

int MultiRollDie::min() const
{
    return num_rolls_ * die_->min();
}

int MultiRollDie::max() const
{
    return num_rolls_ * die_->max();
}

} // namespace dice
