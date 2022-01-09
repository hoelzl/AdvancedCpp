// ReSharper disable CppClangTidyCppcoreguidelinesAvoidCArrays
#include "global_error_code.hpp"

#include <cerrno>
#include <cmath>

namespace global_error_code {

void domain_error() { errno = EDOM; }

void out_of_memory_error() { errno = ENOMEM; }

bool compute_sum(double lhs, double rhs, double& result) noexcept
{
    result = lhs + rhs;
    return true;
}

bool compute_sqrt(double arg, double& result) noexcept
{
    if (arg < 0) {
        domain_error();
        return false;
    }
    result = sqrt(arg);
    return true;
}

bool allocate_double_array(int size, std::unique_ptr<double[]>& result) noexcept
{
    if (size > 100) {
        out_of_memory_error();
        return false;
    }

    result = std::make_unique<double[]>(static_cast<size_t>(size));
    return true;
}

bool create_array(int size, std::unique_ptr<double[]>& result) noexcept
{
    const auto success{allocate_double_array(size, result)};

    if (success) {
        const int delta{size / 2};
        for (auto i = 0; i < size; ++i) {
            double value = NAN;

            if (const auto local_success{compute_sqrt(i - delta, value)};
                !local_success) {
                static_cast<void>(compute_sqrt(delta - i, value));
            }

            result[i] = round(value * value);
        }
    }
    return success;
}
} // namespace global_error_code