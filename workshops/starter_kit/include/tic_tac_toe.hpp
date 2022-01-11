#pragma once
#ifndef TIC_TAC_TOE_HPP
#define TIC_TAC_TOE_HPP
#include <array>
#include <set>
#include <tuple>

namespace ttt_v2 {

enum class FieldValue
{
    empty,
    black,
    white,
};

class Board
{
public:
    using FieldsType = std::array<FieldValue, 9>;
    using Position = std::pair<short, short>;
    using Moves = std::set<Position>;
    using iterator = FieldsType::iterator;
    using const_iterator = FieldsType::const_iterator;
    using size_type = FieldsType::size_type;
    static constexpr int board_size{9};

    constexpr Board() = default;
    
    [[nodiscard]] iterator begin() { return fields_.begin(); }
    [[nodiscard]] iterator end() { return fields_.end(); }

    [[nodiscard]] FieldsType& fields() { return fields_; }
    [[nodiscard]] const FieldsType& fields() const { return fields_; }

    [[nodiscard]] FieldValue field_value(Position pos) const;
    void set_field_value(Position pos, FieldValue value);

    [[nodiscard]] bool is_move_valid(Position pos) const;
    [[nodiscard]] Moves valid_moves() const;
    [[nodiscard]] Moves valid_moves_with_error() const;

    static const std::array<Position, board_size>& all_positions();
    static std::array<Position, board_size> all_positions_with_error();

private:
    FieldsType fields_{};
    static size_type compute_linear_index(Position pos);
    static std::array<Position, board_size> compute_all_positions();
};
}

#endif // TIC_TAC_TOE_HPP