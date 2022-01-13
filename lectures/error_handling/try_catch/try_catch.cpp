// ReSharper disable CppClangTidyCppcoreguidelinesAvoidCArrays
#include "try_catch.hpp"

#include <cmath>
#include <memory>
#include <stdexcept>
#include <string>

namespace try_catch {

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
    for (auto i = 0; i < size; ++i) {
        // Using try/catch inside the normal flow of control.
        // This is definitely bad style!
        try {
            result[i] = round(compute_sqrt(i - delta) * compute_sqrt(i - delta));
        }
        catch (const std::out_of_range& x) {
            result[i] = round(compute_sqrt(delta - i) * compute_sqrt(delta - i));
        }
    }
    return result;
}
} // namespace try_catch