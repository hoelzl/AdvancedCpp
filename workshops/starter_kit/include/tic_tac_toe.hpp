#pragma once
#ifndef TIC_TAC_TOE_HPP
#define TIC_TAC_TOE_HPP
#include <array>

namespace ttt {

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
    using iterator = FieldsType::iterator;
    using const_iterator = FieldsType::const_iterator;

    iterator begin() { return fields_.begin(); }
    iterator end() { return fields_.end(); }

private:
    FieldsType fields_{};
};

}

#endif // TIC_TAC_TOE_HPP