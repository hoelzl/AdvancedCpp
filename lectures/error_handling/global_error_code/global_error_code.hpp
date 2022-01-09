// ReSharper disable CppClangTidyCppcoreguidelinesAvoidCArrays
#pragma once

#include <memory>

namespace global_error_code {

void domain_error();
void out_of_memory_error();

[[nodiscard]] bool compute_sum(double lhs, double rhs, double& result) noexcept;

[[nodiscard]] bool compute_sqrt(double arg, double& result) noexcept;

[[nodiscard]] bool
allocate_double_array(int size, std::unique_ptr<double[]>& result) noexcept;

[[nodiscard]] bool create_array(int size, std::unique_ptr<double[]>& result) noexcept;

} // namespace global_error_code