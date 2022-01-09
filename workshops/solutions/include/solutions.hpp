#pragma once
#ifndef SOLUTIONS_HPP
#define SOLUTIONS_HPP
#include <stdexcept>
#include <vector>
#include <functional>
#include <set>

namespace sol {

enum class Op { add, mul };

std::function<int(int, int)> get_op_impl_1(Op op);

inline auto get_op_impl_2(Op op)
{
    return [op](int m, int n) {
        switch (op) {
        case Op::add: return m + n;
        case Op::mul: return m * n;
        }
        throw std::runtime_error("Unimplemented operation found.");
    };
}

using BinaryIntFunPtr = int (*)(int, int);

BinaryIntFunPtr get_op_impl_3(Op op);

int sum_from_to(int min, int max);

void remove_duplicates(std::vector<int>& v);

std::set<int> without_duplicates(const std::vector<int>& v);

} // namespace sol

#endif // SOLUTIONS_HPP
