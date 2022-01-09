// ReSharper disable CppClangTidyCppcoreguidelinesAvoidCArrays
#pragma once

#include <memory>

namespace error_code_with_query {

enum class Status
{
    none,
    domain_error,
    out_of_memory_error
};

void domain_error();
void out_of_memory_error();

void clear_status();
Status get_status();

double compute_sum(double lhs, double rhs) noexcept;
double compute_sqrt(double arg) noexcept;
std::unique_ptr<double[]> allocate_double_array(int size) noexcept;
std::unique_ptr<double[]> create_array(int size) noexcept;

} // namespace error_code_with_query