#include "int_range.hpp"

#include <iostream>


void run_int_range_v0_example()
{
    for (const int i : stl::IntRangeV0{10, 20}) {
        std::cout << i << "\n";
    }
}
