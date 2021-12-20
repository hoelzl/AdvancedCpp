// ReSharper disable CppClangTidyCppcoreguidelinesProBoundsArrayToPointerDecay
// ReSharper disable CppClangTidyCppcoreguidelinesAvoidCArrays
// ReSharper disable CppClangTidyCppcoreguidelinesProBoundsPointerArithmetic
// ReSharper disable CppClangTidyBugproneExceptionEscape
// ReSharper disable CppClangTidyCppcoreguidelinesProTypeReinterpretCast
#include <iostream>
#include <sstream>
#include <string>

#include "array_dangers.hpp"

#define SHOW_EXPLANATION 1  // NOLINT(cppcoreguidelines-macro-usage)

using namespace pointers;
using namespace std::ranges;

template <typename T>
std::string address_of(T* obj)
{
    std::stringstream os{};
    os << "0x" << std::hex << reinterpret_cast<std::uintptr_t>(obj);
    return os.str();
}

int main()
{
    circle const circles[5]{{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}, {7.0, 8.0}, {9.0, 0.0}};
    shape const* ps = circles;

    std::cout << "Drawing circles via circles.\n\n";
    circles[0].draw();
    circles[3].draw();

    std::cout << "\nDrawing circles via ps."
              << "\n\n";
    (&ps[0])->draw();
    (&ps[3])->draw();

#if SHOW_EXPLANATION // Explanation
    std::cout << "\nExplanation:\n\n";
    std::cout << "Address of circles:    " << address_of(circles) << "\n";
    std::cout << "Address of ps:         " << address_of(ps) << "\n\n";

    std::cout << "Address of circles[1]: " << address_of(circles + 1) << "\n";
    std::cout << "Address of ps[1]:      " << address_of(ps + 1) << "\n";
    std::cout << "Address of ps[3]:      " << address_of(ps + 3) << "\n";

    std::cout << "Size of circle:        " << sizeof(circle) << "\n";
    std::cout << "Size of shape:         " << sizeof(shape) << "\n\n";
#endif
}
