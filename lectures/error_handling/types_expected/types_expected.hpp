// ReSharper disable CppClangTidyCppcoreguidelinesAvoidCArrays
#pragma once

#include <memory>
#include <string>

#include "expected.hpp"

namespace types_expected {

[[nodiscard]] tl::expected<double, std::string>
compute_sum(double lhs, double rhs) noexcept;

[[nodiscard]] tl::expected<double, std::string> compute_sqrt(double arg) noexcept;

[[nodiscard]] tl::expected<std::unique_ptr<double[]>, std::string>
allocate_double_array(int size) noexcept;

[[nodiscard]] tl::expected<std::unique_ptr<double[]>, std::string>
create_array(int size);

}