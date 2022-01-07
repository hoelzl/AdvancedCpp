#pragma once
#ifndef TIC_TAC_TOE_HPP
#define TIC_TAC_TOE_HPP
#include <array>
#include <random>
#include <set>
#include <vector>

namespace ttt {

enum class FieldValue
{
    empty,
    black,
    white,
};

std::ostream& operator<<(std::ostream& os, FieldValue value);

using Position = std::pair<short, short>;

class PlayerColor
{
public:
    static PlayerColor from_string(std::string_view color);
    static PlayerColor from_field_value(FieldValue value);

    // ReSharper disable once CppNonExplicitConversionOperator
    operator FieldValue() const;

    static const PlayerColor black;
    static const PlayerColor white;

private:
    enum class Color
    {
        black,
        white
    };

    explicit PlayerColor(Color color) : color_{color} {}

    Color color_;
};

PlayerColor other_player_color(PlayerColor pc);

bool is_position_valid(Position pos);

class Board
{
public:
    using FieldsType = std::array<FieldValue, 9>;
    using size_type = FieldsType::size_type;
    // using size_type = decltype(std::ssize(FieldsType{}));
    using iterator = FieldsType::iterator;
    using const_iterator = FieldsType::const_iterator;
    // Define this as std::set when creating initial implementation.
    using Moves = std::vector<Position>;
    using Configuration = std::set<Position>;

    [[nodiscard]] iterator begin() { return fields_.begin(); }
    [[nodiscard]] iterator end() { return fields_.end(); }
    [[nodiscard]] const_iterator cbegin() const { return fields_.cbegin(); }
    [[nodiscard]] const_iterator cend() const { return fields_.cend(); }

    [[nodiscard]] static const std::array<Position, 9>& all_positions();
    [[nodiscard]] Configuration configuration(PlayerColor pc) const;

    [[nodiscard]] static std::set<Configuration>& winning_configurations();
    [[nodiscard]] static bool is_winning_configuration(const Configuration& conf);

    [[nodiscard]] FieldValue field_value(Position pos) const;
    void set_field_value(Position pos, FieldValue value);

    [[nodiscard]] bool is_move_valid(Position pos) const;
    [[nodiscard]] Moves valid_moves() const;

    void move(PlayerColor pc, Position pos);

private:
    FieldsType fields_{};

    [[nodiscard]] static size_type compute_linear_index(Position pos);
    [[nodiscard]] static std::array<Position, 9> compute_all_positions();
};

std::string to_string(const Board& board, int prefix_len = 0);

using random_engine = std::default_random_engine;

void play_automated_game(random_engine::result_type seed = random_engine::default_seed);

} // namespace ttt

#endif // TIC_TAC_TOE_HPP
