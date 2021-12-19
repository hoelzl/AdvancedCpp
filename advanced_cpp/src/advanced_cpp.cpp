#include "advanced_cpp.hpp"

#include <iostream>
#include <numeric>

void write_greeting(std::string_view const name) {
    std::cout << "Hello " << name << ", from the advanced C++ course.\n";
}

int add_ints(gsl::span<int> const ints) {
    auto result = 0;
    for (auto i = 0u; i < ints.size(); ++i) { // NOLINT(modernize-loop-convert)
        result += ints[i];
    }
    auto const result2 = std::accumulate(begin(ints), end(ints), 0);

    // This is not a good assertion...
    Ensures(result == result2);
    return result;
}
