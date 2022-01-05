#include "advanced_cpp.hpp"

#include <iostream>
#include <numeric>

void write_greeting(const std::string_view name) {
    std::cout << "Hello " << name << ", from the advanced C++ course.\n";
}

int add_ints(const std::span<int> ints) {
    auto result = 0;
    for (auto i = 0u; i < ints.size(); ++i) { // NOLINT(modernize-loop-convert)
        result += ints[i];
    }
    const auto result2 = std::accumulate(begin(ints), end(ints), 0);

    // This is not a good assertion...
    Ensures(result == result2);
    return result;
}
