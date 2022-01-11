// ReSharper disable CppUseRangeAlgorithm
#include "tic_tac_toe.hpp"

#include <algorithm>
#include <cassert>
#include <ranges>

namespace ttt_v2 {
FieldValue Board::field_value(Position pos) const
{
    return fields_.at(compute_linear_index(pos));
}

void Board::set_field_value(Position pos, FieldValue value)
{
    fields_.at(compute_linear_index(pos)) = value;
}

bool Board::is_move_valid(Position pos) const
{
    return field_value(pos) == FieldValue::empty;
}

Board::Moves Board::valid_moves() const
{
    Board::Moves result{};
    const auto positions{all_positions()};
    std::remove_copy_if(
        positions.cbegin(), positions.cend(), std::inserter(result, result.begin()),
        [this](auto pos) { return !is_move_valid(pos); });
    return result;
}

Board::Moves Board::valid_moves_with_error() const
{
    Board::Moves result{};
    std::remove_copy_if(
        all_positions().cbegin(), all_positions().cend(),
        std::inserter(result, result.begin()),
        [this](auto pos) { return !is_move_valid(pos); });
    return result;
}

Board::size_type Board::compute_linear_index(Position pos)
{
    const auto result{pos.first + 3 * pos.second};
    // assert(0 <= result && result < board_size);
    return result;
}
//
// std::array<Board::Position, board_size> Board::compute_all_positions()
//{
//    std::array<Position, board_size> result{};
//    auto indices{std::views::iota(0, board_size)};
//    std::ranges::for_each(indices, [&result](int idx) {
//        result.at(idx) = {idx / 3, idx % 3};
//    });
//    return result;
//}

auto Board::compute_all_positions() -> std::array<Position, board_size>
{
    std::array<Position, board_size> result{};
    for (short idx{0}; idx < board_size; ++idx) {
        result.at(idx) = {idx / 3, idx % 3};
    }
    return result;
}

const std::array<Board::Position, Board::board_size>& Board::all_positions()
{
    static const auto results{compute_all_positions()};
    return results;
}

std::array<Board::Position, Board::board_size> Board::all_positions_with_error()
{
    static const auto results{compute_all_positions()};
    return results;
}

} // namespace ttt_v2
