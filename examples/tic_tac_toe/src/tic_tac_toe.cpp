// ReSharper disable CppClangTidyPerformanceInefficientStringConcatenation
#include "tic_tac_toe.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <random>
#include <ranges>
#include <sstream>
#include <utility>
#include <vector>

#define USE_FOR_LOOP_IMPLEMENTATION 0 // NOLINT(cppcoreguidelines-macro-usage)

using namespace std::literals::string_literals;
namespace rng = std::ranges;

namespace ttt {

#if USE_FOR_LOOP_IMPLEMENTATION

std::array<Position, 9> Board::compute_all_positions()
{
    std::array<Position, 9> result{};
    for (short x = 0; x < 3; ++x) {
        for (short y = 0; y < 3; ++y) {
            result.at(compute_linear_index({x, y})) = {x, y};
        }
    }
    return result;
}

#else

std::array<Position, 9> Board::compute_all_positions()
{
    std::array<Position, 9> result{};
    auto indices{std::views::iota(0, 9)};
    rng::for_each(indices, [&result](auto idx) { result[idx] = {idx / 3, idx % 3}; });
    return result;
}

#endif

std::ostream& operator<<(std::ostream& os, FieldValue value)
{
    switch (value) {
    case FieldValue::empty: os << "empty"; break;
    case FieldValue::black: os << "black"; break;
    case FieldValue::white: os << "white"; break;
    }
    return os;
}

PlayerColor PlayerColor::from_string(std::string_view color)
{
    if (color == "black") {
        return black;
    }
    if (color == "white") {
        return white;
    }
    throw std::invalid_argument(
        "Cannot create player with color " + std::string{color} + ".");
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

PlayerColor other_player_color(PlayerColor pc)
{
    if (pc == PlayerColor::black) {
        return PlayerColor::white;
    }
    if (pc == PlayerColor::white) {
        return PlayerColor::black;
    }
    throw std::runtime_error("Should not happen.");
}

bool is_position_valid(Position pos)
{
    return 0 <= pos.first && pos.first < 3 && 0 <= pos.second && pos.second < 3;
}

const std::array<Position, 9>& Board::all_positions()
{
    static const std::array<Position, 9> result{compute_all_positions()};
    return result;
}

Board::Configuration Board::configuration(PlayerColor pc) const
{
    auto result{
        std::views::all(all_positions()) | std::views::filter([pc, this](Position pos) {
            return field_value(pos) == pc;
        })};
    return {result.begin(), result.end()};
}

std::set<Board::Configuration>& Board::winning_configurations()
{
    static std::set<Configuration> wins{
        // clang-format off
        // Diagonals
        {{0, 0}, {1, 1}, {2, 2}},
        {{2, 0}, {1, 1}, {0, 2}},
        // Rows
        {{0, 0}, {0, 1}, {0, 2}},
        {{1, 0}, {1, 1}, {1, 2}},
        {{2, 0}, {2, 1}, {2, 2}},
        // Columns
        {{0, 0}, {1, 0}, {2, 0}},
        {{0, 1}, {1, 1}, {2, 1}},
        {{0, 2}, {1, 2}, {2, 2}}
        // clang-format on
    };
    return wins;
}

int num_shared_members(const Board::Configuration& lhs, const Board::Configuration& rhs)
{
    //return std::reduce(lhs.cbegin(), lhs.cend(), 0, [&rhs](int i, Position pos) {
    //    return rhs.contains(pos) ? i + 1 : i;
    //});
    auto result{0};
    for (auto pos : lhs) {
        if (rhs.contains(pos))
        {
            ++result;
        }
    }
    return result;
}

bool Board::is_winning_configuration(const Configuration& conf)
{
    using std::views::all;
    using std::views::filter;
    using std::views::take;

    auto winning_conf_range{
        all(winning_configurations()) | filter([conf](const Configuration& winning) {
            return num_shared_members(conf, winning) >= 3;
        })
        | take(1)};
    return !winning_conf_range.empty();
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

Board::Moves Board::valid_moves() const
{
    auto positions = rng::views::filter(
        all_positions(), [this](auto pos) { return is_move_valid(pos); });
    return {positions.begin(), positions.end()};
}

void Board::move(PlayerColor pc, Position pos)
{
    if (!is_move_valid(pos)) {
        throw std::invalid_argument{"Move to an invalid position."};
    }
    set_field_value(pos, pc);
}

Board::size_type Board::compute_linear_index(Position pos)
{
    const auto result{static_cast<size_type>(pos.first + 3 * pos.second)};
    assert(result < 9);
    return result;
}


char to_char(FieldValue field_value)
{
    switch (field_value) {
    case FieldValue::empty: return ' ';
    case FieldValue::black: return 'x';
    case FieldValue::white: return 'o';
    }
    throw std::invalid_argument{"Should not happen."};
}

std::string to_string(const Board& board, int prefix_len)
{
    std::ostringstream os{};

    const auto prefix{std::string(prefix_len, ' ')};
    const auto separator{std::string(9, '-')};
    auto row_prefix{""s};

    for (auto row{0}; row < 3; ++row) {
        auto column_prefix{prefix};
        os << row_prefix;
        for (auto column{0}; column < 3; ++column) {
            os << column_prefix << to_char(board.field_value({row, column}));
            column_prefix = " | ";
        }
        row_prefix = "\n"s + prefix + separator + "\n"s;
    }
    return os.str();
}

void play_automated_game(random_engine::result_type seed)
{
    auto current_player{PlayerColor::black};
    auto board{Board{}};
    std::default_random_engine gen{seed};

    std::cout << "Starting a new game.\nRandom seed is " << seed << "\n\n";
    for (;;) {
        auto possible_moves{board.valid_moves()};
        if (possible_moves.empty()) {
            std::cout << "\nGame over!\nIt was a tie.\n\n";
            break;
        }
        std::ranges::shuffle(possible_moves, gen);
        const auto move{possible_moves[0]};
        std::cout << "Player '" << current_player << "' plays " << move.first + 1
                  << ", " << move.second + 1 << "\n";
        board.move(current_player, move);
        if (Board::is_winning_configuration(board.configuration(current_player))) {
            std::cout << "\nGame over!\n";
            std::cout << "Player '" << current_player << "' won.\n\n";
            break;
        }
        current_player = other_player_color(current_player);
    }
    std::cout << to_string(board, 4) << "\n\n";
}

} // namespace ttt
