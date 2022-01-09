// ReSharper disable CppClangTidyCppcoreguidelinesAvoidCArrays
#include "error_code_with_query.hpp"

#include <cmath>

namespace error_code_with_query {

namespace {
Status current_status{Status::none};  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)
}

void domain_error() { current_status = Status::domain_error; }

void out_of_memory_error() { current_status = Status::out_of_memory_error; }

void clear_status() { current_status = Status::none; }

Status get_status() { return current_status; }

double compute_sum(double lhs, double rhs) noexcept { return lhs + rhs; }

double compute_sqrt(double arg) noexcept
{
    if (arg < 0) {
        domain_error();
        return 0.0;
    }
    return sqrt(arg);
}

std::unique_ptr<double[]> allocate_double_array(int size) noexcept
{
    if (size > 100) {
        out_of_memory_error();
        return std::unique_ptr<double[]>{};
    }

    try {
        return std::make_unique<double[]>(static_cast<size_t>(size));
    }
    catch (std::bad_alloc&) {
        // This is unlikely to work and very difficult to test!
        out_of_memory_error();
        return std::unique_ptr<double[]>{};
    }
}

std::unique_ptr<double[]> create_array(int size) noexcept
{
    // Don't do this?
    clear_status();
    auto result{allocate_double_array(size)};

    if (get_status() == Status::none) {
        const int delta{size / 2};
        for (int i = 0; i < size; ++i) {
            auto value{compute_sqrt(i - delta)};

            if (get_status() != Status::none) {
                clear_status();
                value = compute_sqrt(delta - i);
            }
            (result.get())[i] = round(value * value);
        }
    }
    return result;
}
} // namespace error_code_with_query