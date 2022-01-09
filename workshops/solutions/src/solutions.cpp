#include "solutions.hpp"

#include <algorithm>
#include <iterator>
#include <numeric>

#include "int_range.hpp"

namespace sol {

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
    auto ir{stl::IntRangeV0{min, max}};
    return std::accumulate(ir.begin(), ir.end(), 0);
}

void remove_duplicates(std::vector<int>& v)
{
    std::ranges::sort(v);
    auto unique_range{std::ranges::unique(v)};
    v.erase(unique_range.begin(), unique_range.end());
}

std::set<int> without_duplicates(const std::vector<int>& v)
{
    std::set<int> result{};
    std::ranges::copy(v, std::inserter(result, result.begin()));
    return result;
}

} // namespace sol
