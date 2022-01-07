#include "advanced_cpp.hpp"

#include <iostream>

namespace advanced_cpp {

void print_advanced_cpp_info()
{
    std::cout << "Subproject Info\n\n";
    std::cout << "  name:      advanced_cpp\n";
    std::cout << "  namespace: advanced_cpp\n";
}

int compute_sum(int m, int n) { return m + n; }

bool pessimistic_estimate() { return false; }

void throw_an_exception() { throw std::invalid_argument("There is no argument?"); }

} // namespace advanced_cpp
