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

int sum_from_to(int min, int max)
{
    auto ir{IntRangeV0{min, max}};
    return std::accumulate(ir.begin(), ir.end(), 0);
}

} // namespace sol
