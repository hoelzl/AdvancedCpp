#include "tic_tac_toe.hpp"

#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <ranges>

using ttt::Board;
using ttt::FieldValue;
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
