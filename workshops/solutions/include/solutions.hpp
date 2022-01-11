#pragma once
#ifndef SOLUTIONS_HPP
#define SOLUTIONS_HPP

#include <functional>
#include <iostream>
#include <set>
#include <stdexcept>
#include <vector>

namespace sol {

enum class Op
{
    add,
    mul
};

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

namespace outer::middle {
struct Person
{
    std::string name;
};

//namespace inner {
//std::ostream& operator<<(std::ostream& os, Person person);
//}

std::ostream& operator<<(std::ostream& os, Person person);
} // namespace outer::middle

namespace outer {
// std::ostream& operator<<(std::ostream& os, middle::Person person);
}

#endif // SOLUTIONS_HPP
