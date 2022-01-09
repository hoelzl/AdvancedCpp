#include "solutions.hpp"

#include <iostream>
#include <numeric>

namespace sol {

void run_int_range_v0_example()
{
    for (const int i : IntRangeV0{10, 20}) {
        std::cout << i << "\n";
    }
}

std::function<int(int, int)> get_op_impl_1(Op op)
{
    switch (op) {
    case Op::add: return [](int m, int n) { return m + n; };
    case Op::mul: return [](int m, int n) { return m * n; };
    }
    throw std::runtime_error("Unimplemented operation found.");
}

int add(int m, int n) { return m + n; }
int mul(int m, int n) { return m * n; }

BinaryIntFunPtr get_op_impl_3(Op op)
{
    switch (op) {
    case Op::add: return &add;
    case Op::mul: return &mul;
    }
    throw std::runtime_error("Unimplemented operation found.");
}

int sum_from_to(int min, int max)
{
    auto ir{IntRangeV0{min, max}};
    return std::accumulate(ir.begin(), ir.end(), 0);
}

} // namespace sol
