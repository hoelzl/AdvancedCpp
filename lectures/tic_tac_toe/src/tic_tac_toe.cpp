#include "tic_tac_toe.hpp"

#include <cassert>
#include <iostream>
#include <ranges>

namespace rng = std::ranges;

namespace ttt {

std::set<Position> compute_all_positions()
{
    std::set<Position> result{};
    for (short x = 0; x < 3; ++x) {
        for (short y = 0; y < 3; ++y) {
            result.insert({x, y});
        }
    }
    return result;
}

std::set<Position> compute_all_positions_v2()
{
    auto indices{rng::views::iota(0, 9)};
    const auto pairs = indices | rng::views::transform([](auto idx) {
                           return std::make_pair<short, short>(idx / 3, idx % 3);
                       });
    return {std::cbegin(pairs), std::cend(pairs)};
}

std::ostream& operator<<(std::ostream& os, FieldValue value)
{
    using enum FieldValue;
    switch (value) {
    case empty: os << "empty"; break;
    case white: os << "white"; break;
    case black: os << "black"; break;
    }
    return os;
}

PlayerColor PlayerColor::from_string(std::string_view color)
{
    if (color == "black") {
        return black;
    }
    else if (color == "white") {
        return white;
    }
    throw std::invalid_argument("Cannot create player with color " + std::string{color} + ".");
}

PlayerColor PlayerColor::from_field_value(FieldValue value)
{
    switch (value) {
    case FieldValue::black: return black;
    case FieldValue::white: return white;
    case FieldValue::empty:
        throw std::invalid_argument("Cannot create a player color from empty field.");
    }
    throw std::runtime_error("Should not happen.");
}

PlayerColor::operator FieldValue() const
{
    switch (color_) {
    case Color::black: return FieldValue::black;
    case Color::white: return FieldValue::white;
    }
    throw std::runtime_error("Should not happen.");
}

const PlayerColor PlayerColor::black{Color::black};
const PlayerColor PlayerColor::white{Color::white};

bool is_position_valid(Position pos)
{
    return 0 <= pos.first && pos.first < 3 && 0 <= pos.second && pos.second < 3;
}

const std::set<Position>& Board::all_positions()
{
    static const std::set<Position> result{compute_all_positions()};
    return result;
}

FieldValue Board::field_value(Position pos) const
{
    return fields_[compute_linear_index(pos)];
}

void Board::set_field_value(Position pos, FieldValue value)
{
    fields_[compute_linear_index(pos)] = value;
}

bool Board::is_move_valid(Position pos) const
{
    return field_value(pos) == FieldValue::empty;
}

std::set<Position> Board::valid_moves() const
{
    auto positions = rng::views::filter(
        all_positions(), [this](auto pos) { return is_move_valid(pos); });
    return {positions.begin(), positions.end()};
}

Board::size_type Board::compute_linear_index(Position pos)
{
    const auto result{static_cast<size_type>(pos.first + 3 * pos.second)};
    assert(result < 9);
    return result;
}
} // namespace ttt
