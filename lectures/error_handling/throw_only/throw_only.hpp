// ReSharper disable CppClangTidyCppcoreguidelinesAvoidCArrays
#pragma once

#include <memory>

namespace throw_only {

double compute_sum(double lhs, double rhs) noexcept;

double compute_sqrt(double arg);

std::unique_ptr<double[]> allocate_double_array(int size);

std::unique_ptr<double[]> create_array(int size);
}