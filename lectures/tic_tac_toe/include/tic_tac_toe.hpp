#pragma once
#ifndef TIC_TAC_TOE_HPP
#define TIC_TAC_TOE_HPP
#include <array>
#include <set>

namespace ttt {

enum class FieldValue
{
    empty,
    white,
    black,
};

using Position = std::pair<short, short>;

bool is_position_valid(Position pos);

class Board
{
public:
    using fields_type = std::array<FieldValue, 9>;
    using size_type = fields_type::size_type;
    // using size_type = decltype(std::ssize(fields_type{}));
    using iterator = fields_type::iterator;
    using const_iterator = fields_type::const_iterator;

    [[nodiscard]] iterator begin() { return fields_.begin(); }
    [[nodiscard]] iterator end() { return fields_.end(); }
    [[nodiscard]] const_iterator cbegin() const { return fields_.cbegin(); }
    [[nodiscard]] const_iterator cend() const { return fields_.cend(); }

    [[nodiscard]] static const std::set<Position>& all_positions();

    [[nodiscard]] FieldValue field_value(Position pos) const;
    void set_field_value(Position pos, FieldValue value);

    [[nodiscard]] bool is_move_valid(Position pos) const;
    [[nodiscard]] std::set<Position> valid_moves() const;

private:
    fields_type fields_{};

    [[nodiscard]] static size_type compute_linear_index(Position pos);
};

} // namespace ttt

#endif // TIC_TAC_TOE_HPP
