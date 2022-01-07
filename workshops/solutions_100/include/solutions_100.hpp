#pragma once
#ifndef SOLUTIONS_100_HPP
#define SOLUTIONS_100_HPP
#include <stdexcept>
#include <vector>

namespace sol_100 {

class IntRangeV0
{
private:
    std::vector<int> numbers_{};

public:
    using iterator = decltype(numbers_)::iterator;

    IntRangeV0(int min, int max)
    {
        if (min > max) {
            throw std::invalid_argument("min must be <= max.");
        }
        for (int i{min}; i <= max; ++i) {
            numbers_.push_back(i);
        }
    }

    iterator begin() { return numbers_.begin(); }
    iterator end() { return numbers_.end(); }
};

void run_int_range_v0_example();

int sum_from_to(int min, int max);

} // namespace sol_100

#endif // SOLUTIONS_100_HPP
