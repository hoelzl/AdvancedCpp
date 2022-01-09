// ReSharper disable CppClangTidyCppcoreguidelinesAvoidCArrays
#include "throw_only.hpp"

#include <cmath>
#include <memory>
#include <stdexcept>
#include <string>

namespace throw_only {

using namespace std::string_literals;

double compute_sum(double lhs, double rhs) noexcept { return lhs + rhs; }

double compute_sqrt(double arg)
{
    if (arg < 0) {
        throw std::out_of_range{"Cannot compute square root of negative number."s};
    }
    return sqrt(arg);
}

std::unique_ptr<double[]> allocate_double_array(int size)
{
    if (size > 100) {
        throw std::bad_alloc{};
    }

    return std::make_unique<double[]>(size);
}

std::unique_ptr<double[]> create_array(int size)
{
    std::unique_ptr<double[]> result{allocate_double_array(size)};
    const int delta{size / 2};
    for (int i = 0; i < size; ++i) {
        const int value{i - delta >= 0 ? i - delta : delta - i};
        result[i] = round(compute_sqrt(value) * compute_sqrt(value));
    }
    return result;
}

} // namespace throw_only