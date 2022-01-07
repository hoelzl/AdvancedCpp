// ReSharper disable CppClangTidyBugproneExceptionEscape
// ReSharper disable CppClangTidyCppcoreguidelinesProBoundsPointerArithmetic
#include <iostream>

#include "tic_tac_toe.hpp"

constexpr bool run_asan_stack_example{false};
constexpr bool run_asan_heap_example{false};

int main()
{
    if constexpr (run_asan_stack_example) {
        constexpr int stack_array[9]{}; // NOLINT(cppcoreguidelines-avoid-c-arrays)
        constexpr int x{}, y{}, z{};
        std::cout << &x << ", " << &y << ", " << &z << "\n";
        std::cout << stack_array[9] << "\n"; // NOLINT(clang-diagnostic-array-bounds)
    }

    if constexpr (run_asan_heap_example) {
        const int* heap_array = new int[9];
        std::cout << heap_array[9] << "\n";
    }

    ttt::play_automated_game(3);

    ttt::play_automated_game();
    for (auto seed{0u}; seed < 10u; ++seed) {
        ttt::play_automated_game(seed);
    }
}
