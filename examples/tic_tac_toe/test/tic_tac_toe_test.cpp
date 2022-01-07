#include "tic_tac_toe.hpp"

#include <algorithm>
#include <ranges>
#include <sstream>

#include "catch2/catch_test_macros.hpp"

namespace rng = std::ranges;

TEST_CASE("Board()")
{

    ttt::Board board{};

    SECTION("Default constructed board has empty fields.")
    {
        for (auto field : board) {
            CHECK(field == ttt::FieldValue::empty);
        }

        // ReSharper disable once CppUseRangeAlgorithm
        std::for_each(board.cbegin(), board.cend(), [](auto field) {
            CHECK(field == ttt::FieldValue::empty);
        });

        // Or with a single check:
        CHECK(std::all_of(board.cbegin(), board.cend(), [](auto field) {
            return field == ttt::FieldValue::empty;
        }));

        static_assert(std::random_access_iterator<ttt::Board::iterator>);
        static_assert(std::contiguous_iterator<ttt::Board::iterator>);
        static_assert(std::contiguous_iterator<ttt::Board::const_iterator>);

        // Valid since board's iterator is a `random_access_iterator` (actually even the
        // stronger `contiguous_iterator`).
        CHECK(board.cend() - board.cbegin() == 9);

        // Probably better:
        CHECK(std::distance(board.cbegin(), board.cend()) == 9);

        // That's not good... We are dereferencing a non-dereferenceable pointer.
        // CHECK(*board.cend() == ttt::FieldValue::empty);

        // If ranges are available:
        rng::for_each(
            board, [](auto field) { CHECK(field == ttt::FieldValue::empty); });
        CHECK(rng::all_of(
            board, [](auto field) { return field == ttt::FieldValue::empty; }));
        CHECK(rng::distance(board) == 9);
    }

    SECTION("The generated positions are correct.")
    {
        auto all_positions{ttt::Board::all_positions()};
        CHECK(rng::distance(all_positions) == 9);
        CHECK(rng::all_of(all_positions, ttt::is_position_valid));
    }

    SECTION("Reading and writing field values works.")
    {
        for (auto x : rng::views::iota(0, 3)) {
            for (auto y : rng::views::iota(0, 3)) {
                CHECK(board.field_value({x, y}) == ttt::FieldValue::empty);
            }
        }

        board.set_field_value({0, 0}, ttt::FieldValue::white);
        CHECK(board.field_value({0, 0}) == ttt::FieldValue::white);
        board.set_field_value({1, 2}, ttt::FieldValue::black);
        CHECK(board.field_value({1, 2}) == ttt::FieldValue::black);
        board.set_field_value({2, 1}, ttt::FieldValue::white);
        CHECK(board.field_value({2, 1}) == ttt::FieldValue::white);

        // Fields that were not changed retain their value
        CHECK(board.field_value({0, 1}) == ttt::FieldValue::empty);
    }

    SECTION("Valid moves are correctly computed.")
    {
        ttt::Board non_empty_board{};
        std::set<ttt::Position> white_moves{{0, 0}, {2, 0}, {2, 1}};
        std::set<ttt::Position> black_moves{{0, 1}, {1, 2}, {2, 2}};

        std::set<ttt::Position> all_played_moves{white_moves};
        all_played_moves.insert(black_moves.cbegin(), black_moves.cend());

        for (auto pos : white_moves) {
            non_empty_board.set_field_value(pos, ttt::FieldValue::white);
        }
        for (auto pos : black_moves) {
            non_empty_board.set_field_value(pos, ttt::FieldValue::black);
        }

        // This is too complex for a real test, but we want to show lambda capture...
        CHECK(rng::all_of(
            ttt::Board::all_positions(),
            [&all_played_moves, &non_empty_board](auto pos) {
                return rng::find(all_played_moves, pos) == all_played_moves.end()
                           ? non_empty_board.is_move_valid(pos)
                           : !non_empty_board.is_move_valid(pos);
            }));
    }

    SECTION("Field values can be written to an ostream.")
    {
        std::ostringstream os{};

        SECTION("Empty field value can be written.")
        {
            os << ttt::FieldValue::empty;
            CHECK(os.str() == "empty");
        }

        SECTION("White field value can be written.")
        {
            os << ttt::FieldValue::white;
            CHECK(os.str() == "white");
        }

        SECTION("White field value can be written.")
        {
            os << ttt::FieldValue::black;
            CHECK(os.str() == "black");
        }
    }
}

TEST_CASE("PlayerColor()")
{
    using enum ttt::FieldValue;
    using ttt::PlayerColor;
    SECTION("Can be created from strings and field values.")
    {
        CHECK(PlayerColor::from_field_value(black) == PlayerColor::black);
        CHECK(PlayerColor::from_string("black") == PlayerColor::black);
        CHECK(PlayerColor::from_field_value(white) == PlayerColor::white);
        CHECK(PlayerColor::from_string("white") == PlayerColor::white);
    }

    SECTION("PC::from_string throws for invalid argument.")
    {
        CHECK_THROWS_AS(PlayerColor::from_string("empty"), std::invalid_argument);
    }

    SECTION("Can be implicitly converted to FieldValue")
    {
        CHECK(PlayerColor::black == ttt::FieldValue::black);
        CHECK(PlayerColor::white == ttt::FieldValue::white);
    }

    // Surprise!?!
    SECTION("Can be compared for equality.")
    {
        CHECK(PlayerColor::black == PlayerColor::black);
        CHECK(PlayerColor::white == PlayerColor::white);
        CHECK(PlayerColor::black != PlayerColor::white);
    }

    SECTION("Can be written to stream")
    {
        std::ostringstream os{};

        SECTION("Black player can be written.")
        {
            os << PlayerColor::black;
            CHECK(os.str() == "black");
        }

        SECTION("White player can be written.")
        {
            os << PlayerColor::white;
            CHECK(os.str() == "white");
        }
    }
}

TEST_CASE("Board::move()")
{
    using enum ttt::FieldValue;
    using ttt::PlayerColor;
    ttt::Board board{};

    SECTION("Performs move on valid position.")
    {
        board.move(PlayerColor::from_field_value(black), {1, 2});
        CHECK(board.field_value({1, 2}) == black);
    }

    SECTION("Raises error on invalid position")
    {
        board.move(PlayerColor::from_field_value(black), {1, 2});

        CHECK_THROWS_AS(
            board.move(PlayerColor::from_field_value(white), {1, 2}),
            std::invalid_argument);
    }
}

TEST_CASE("Board::winning_configurations()")
{
    SECTION("Diagonals are contained in winning configurations.")
    {
        CHECK(ttt::Board::winning_configurations().contains(
            ttt::Board::Configuration{{0, 0}, {1, 1}, {2, 2}}));
        CHECK(ttt::Board::winning_configurations().contains(
            ttt::Board::Configuration{{0, 2}, {1, 1}, {2, 0}}));
    }

    SECTION("Rows are contained in winning configurations.")
    {
        for (constexpr auto rows{std::views::iota(0, 3)}; const auto row : rows) {
            ttt::Board::Configuration conf{{row, 0}, {row, 1}, {row, 2}};
            CHECK(ttt::Board::winning_configurations().contains(conf));
        }
    }

    SECTION("Columns are contained in winning configurations.")
    {
        for (constexpr auto columns{std::views::iota(0, 3)}; const auto col : columns) {
            ttt::Board::Configuration conf{{0, col}, {1, col}, {2, col}};
            CHECK(ttt::Board::winning_configurations().contains(conf));
        }
    }

    SECTION("Random triples of positions are not contained in winning configurations.")
    {
        ttt::Board::Configuration conf{{0, 1}, {1, 1}, {2, 2}};
        CHECK_FALSE(ttt::Board::winning_configurations().contains(conf));
    }
}

TEST_CASE("Board::is_winning_configuration()")
{
    SECTION("Empty configurations are not winning.")
    {
        CHECK_FALSE(ttt::Board::is_winning_configuration(ttt::Board::Configuration{}));
    }

    SECTION("One-element configurations are not winning.")
    {
        CHECK_FALSE(
            ttt::Board::is_winning_configuration(ttt::Board::Configuration{{0, 0}}));
    }

    SECTION("Diagonals are winning configurations.")
    {
        CHECK(ttt::Board::is_winning_configuration(
            ttt::Board::Configuration{{0, 0}, {1, 1}, {2, 2}}));
        CHECK(ttt::Board::is_winning_configuration(
            ttt::Board::Configuration{{0, 2}, {1, 1}, {2, 0}}));
    }

    SECTION("Rows are winning configurations.")
    {
        for (constexpr auto rows{std::views::iota(0, 3)}; const auto row : rows) {
            ttt::Board::Configuration conf{{row, 0}, {row, 1}, {row, 2}};
            CHECK(ttt::Board::is_winning_configuration(conf));
        }
    }

    SECTION("Columns are winning configurations.")
    {
        for (constexpr auto columns{std::views::iota(0, 3)}; const auto col : columns) {
            ttt::Board::Configuration conf{{col, 0}, {col, 1}, {col, 2}};
            CHECK(ttt::Board::is_winning_configuration(conf));
        }
    }
    
    SECTION("Random triples of positions are not winning configurations.")
    {
        ttt::Board::Configuration conf{{0, 1}, {1, 1}, {2, 2}};
        CHECK_FALSE(ttt::Board::is_winning_configuration(conf));
    }

    SECTION("Large sets of positions can be winning configurations.")
    {
        ttt::Board::Configuration conf{{0, 1}, {1, 1}, {1, 2}, {2, 1}, {2, 2}};
        CHECK(ttt::Board::is_winning_configuration(conf));
    }

    SECTION("All positions is a winning configuration.")
    {
        ttt::Board::Configuration all_pos{};
        std::ranges::copy(
            ttt::Board::all_positions(), std::inserter(all_pos, all_pos.end()));
        CHECK(ttt::Board::is_winning_configuration(all_pos));
    }
}
