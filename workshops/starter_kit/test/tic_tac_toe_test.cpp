#include "tic_tac_toe.hpp"

#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <ranges>

using namespace ttt_v2;
// using rng = std::ranges;

TEST_CASE("What is the scope of FieldType?")
{
    Board::FieldsType my_array{};
    CHECK(my_array.size() == 9);
}

TEST_CASE("Iteration over boards.")
{

    Board board{};

    SECTION("Can iterate using for loop")
    {
        for (auto field : board) {
            CHECK(field == FieldValue::empty);
        }

        // ReSharper disable once CppUseRangeAlgorithm
        std::for_each(board.begin(), board.end(), [](auto field) {
            CHECK(field == FieldValue::empty);
        });

        CHECK(std::all_of(board.begin(), board.end(), [](auto field) {
            return field == FieldValue::empty;
        }));

        CHECK(board.end() - board.begin() == 9);
        CHECK(std::distance(board.begin(), board.end()) == 9);

        std::ranges::for_each(
            board, [](auto field) { CHECK(field == FieldValue::empty); });

        CHECK(std::ranges::all_of(
            board, [](auto field) { return field == FieldValue::empty; }));
    }
}

TEST_CASE("field_value()")
{
    Board board{};

    for (short x{0}; x < 3; ++x) {
        for (short y{0}; y < 3; ++y) {
            CHECK(board.field_value({x, y}) == ttt_v2::FieldValue::empty);
        }
    }

    SECTION("get and set field values")
    {
        CHECK_NOTHROW(board.set_field_value({0, 0}, FieldValue::black));
        CHECK(board.field_value({0, 0}) == FieldValue::black);
    }
}

TEST_CASE("is_move_valid()")
{
    Board board{};

    SECTION("Initially all moves are valid") { CHECK(board.is_move_valid({2, 1})); }

    SECTION("Movie is invalid if field is not empty")
    {
        board.set_field_value({1, 2}, FieldValue::black);
        CHECK_FALSE(board.is_move_valid({1, 2}));
    }
}

TEST_CASE("all_positions()")
{
    Board board{};

    SECTION("all_positions() returns all positions")
    {
        const auto positions{Board::all_positions()};
        for (short x{0}; x < 3; ++x) {
            for (short y{0}; y < 3; ++y) {
                CHECK(
                    std::find(
                        positions.cbegin(), positions.cend(), Board::Position{x, y})
                    != positions.cend());
            }
        }
    }
}

TEST_CASE("valid_moves()")
{
    Board board{};

    SECTION("Initially, all moves are valid")
    {
        CHECK(board.valid_moves().size() == 9);
    }

    SECTION("After two moves only seven positions are valid.")
    {
        board.set_field_value({1, 2}, FieldValue::black);
        board.set_field_value({2, 1}, FieldValue::white);
        CHECK(board.valid_moves().size() == 7);
        CHECK_FALSE(board.valid_moves().contains({1, 2}));
        CHECK_FALSE(board.valid_moves().contains({2, 1}));
    }
}

TEST_CASE("valid_moves_with_error() triggers an error")
{
    Board board{};
    CHECK_FALSE(board.valid_moves_with_error().empty());
}
