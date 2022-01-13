// ReSharper disable CppClangTidyCppcoreguidelinesAvoidCArrays
#include "types_expected.hpp"

#include <cmath>

using namespace std::string_literals;

namespace types_expected {
tl::expected<double, std::string> compute_sum(double lhs, double rhs) noexcept
{
    return lhs + rhs;
}

tl::expected<double, std::string> compute_sqrt(double arg) noexcept
{
    if (arg < 0) {
        return tl::make_unexpected("Cannot compute square root of negative number."s);
    }
    return sqrt(arg);
}

tl::expected<std::unique_ptr<double[]>, std::string>
allocate_double_array(int size) noexcept
{
    if (size > 100) {
        return tl::make_unexpected("Cannot allocate double[] with size > 100."s);
    }

    try {
        return std::make_unique<double[]>(size);
    }
    catch (const std::bad_alloc& e) {
        // This is unlikely to work and very difficult to test!
        return tl::make_unexpected("Memory allocation failed for double[]."s);
    }
}

tl::expected<std::unique_ptr<double[]>, std::string> create_array(int size)
{
    auto result{allocate_double_array(size)};

    if (result.has_value()) {
        const int delta{size / 2};
        for (auto i = 0; i < size; ++i) {
            auto value{compute_sqrt(i - delta)};

            if (!value.has_value()) {
                value = compute_sqrt(delta - i);
            }

            result.value()[i] = round(value.value() * value.value());
        }
    }
    return result;
}
} // namespace types_expected