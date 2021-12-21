// ReSharper disable CppClangTidyCertMsc51Cpp
#pragma once
#ifndef RPG_DICE_RPG_DICE_HPP
#define RPG_DICE_RPG_DICE_HPP

#include <iterator>
#include <memory>
#include <numeric>
#include <random>

namespace dice {

using seed_type = std::mt19937::result_type;
constexpr seed_type default_seed{std::mt19937::default_seed};

class Dice
{
public:
    Dice() = default;

    Dice(Dice const& other) = default;
    Dice(Dice&& other) noexcept = default;
    Dice& operator=(Dice const& other) = default;
    Dice& operator=(Dice&& other) noexcept = default;
    virtual ~Dice() = default;

    [[nodiscard]] virtual int roll() = 0;
    [[nodiscard]] virtual int min() const = 0;
    [[nodiscard]] virtual int max() const = 0;
};

class ConstantDie final : public Dice
{
public:
    explicit ConstantDie(int value);

    [[nodiscard]] int roll() override;
    [[nodiscard]] int min() const override;
    [[nodiscard]] int max() const override;

private:
    int value_{};
};

class RandomDice : public Dice
{
public:
    explicit RandomDice(seed_type seed = default_seed);

protected:
    [[nodiscard]] std::mt19937& engine() { return engine_; }

private:
    std::mt19937 engine_{};
};

class UniformRandomDice : public RandomDice
{
public:
    explicit UniformRandomDice(
        int min_value, int max_value, seed_type seed = default_seed)
        : RandomDice{seed}, distribution_{min_value, max_value}
    {}

protected:
    [[nodiscard]] int random_int() { return distribution()(engine()); }

    [[nodiscard]] std::uniform_int_distribution<>& distribution()
    {
        return distribution_;
    }

private:
    std::uniform_int_distribution<> distribution_{};
};

class FairDice final : public UniformRandomDice
{
public:
    FairDice(int num_rolls, int num_sides, seed_type seed = default_seed)
        : UniformRandomDice{1, num_sides, seed}
        , num_rolls_{num_rolls}
        , num_sides_{num_sides}
    {}

    [[nodiscard]] int roll() override;
    [[nodiscard]] int min() const override;
    [[nodiscard]] int max() const override;

private:
    int num_rolls_{};
    int num_sides_{};
};

class SumDice final : public Dice
{
public:
    SumDice() = default;

    template <typename... TDice>
    explicit SumDice(TDice... dice)
    {
        add_dice(dice...);
    }

    template <typename TDie, typename... TDice>
    void add_dice(TDie die, TDice... dice)
    {
        add_die(std::move(die));
        if constexpr (sizeof...(dice) > 0) {
            add_dice<TDice...>(dice...);
        }
    }

    template <typename TDie>
    void add_die(TDie die)
    {
        dice_.push_back(std::make_unique<std::remove_cvref_t<TDie>>(std::move(die)));
    }

    [[nodiscard]] int roll() override;
    [[nodiscard]] int min() const override;
    [[nodiscard]] int max() const override;

private:
    std::vector<std::unique_ptr<Dice>> dice_{};

    template <typename T>
    [[nodiscard]] int accumulate_dice(T op)
    {
        return std::accumulate(std::begin(dice_), std::end(dice_), 0, op);
    }

    template <typename T>
    [[nodiscard]] int accumulate_dice(T op) const
    {
        return std::accumulate(std::begin(dice_), std::end(dice_), 0, op);
    }
};

class SimpleDie final : public UniformRandomDice
{
public:
    explicit SimpleDie(int num_sides, seed_type seed = default_seed)
        : UniformRandomDice{1, num_sides, seed}, num_sides_{num_sides}
    {}

    [[nodiscard]] int roll() override;
    [[nodiscard]] int min() const override;
    [[nodiscard]] int max() const override;

private:
    int num_sides_{};
};

class MultiRollDie final : public Dice
{
public:
    template <typename TDie>
    explicit MultiRollDie(int num_rolls, TDie die)
        : num_rolls_{num_rolls}, die_{std::make_unique<TDie>(std::move(die))}
    {}

    [[nodiscard]] int roll() override;
    [[nodiscard]] int min() const override;
    [[nodiscard]] int max() const override;

private:
    int num_rolls_{};
    std::unique_ptr<Dice> die_{};
};

} // namespace dice

#endif // RPG_DICE_RPG_DICE_HPP
