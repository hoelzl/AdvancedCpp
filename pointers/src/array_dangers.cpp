// ReSharper disable CppClangTidyCppcoreguidelinesAvoidCArrays
// ReSharper disable CppClangTidyCppcoreguidelinesProBoundsArrayToPointerDecay
// ReSharper disable CppClangTidyCppcoreguidelinesProBoundsPointerArithmetic
#include <iostream>

#include "utils.hpp"
#include "shapes.hpp"

namespace pointers {

namespace {
auto constexpr show_explanation = true;
}

void show_bad_array_access()
{
    Circle const circles[5]{{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}, {7.0, 8.0}, {9.0, 0.0}};
    Circle const* pc = circles;
    Shape const* ps = circles;

    std::cout << "Drawing circles via circles[].\n\n";
    std::cout << "circles[0]: ";
    circles[0].draw();
    std::cout << "circles[3]: ";
    circles[3].draw();

    std::cout << "\nDrawing circles via pc.\n\n";
    std::cout << "&pc[0]: ";
    (&pc[0])->draw();
    std::cout << "&pc[3]: ";
    (&pc[3])->draw();

    std::cout << "\nDrawing circles via ps.\n\n";
    std::cout << "&ps[0]: ";
    (&ps[0])->draw();
    std::cout << "&ps[3]: ";
    (&ps[3])->draw();

    if constexpr (show_explanation) {
        std::cout << "\nExplanation:\n\n";
        std::cout << "Address of circles:    " << address_of(circles) << "\n";
        std::cout << "Address of pc:         " << address_of(pc) << "\n";
        std::cout << "Address of ps:         " << address_of(ps) << "\n\n";

        std::cout << "Address of circles[1]: " << address_of(circles + 1) << "\n";
        std::cout << "Address of pc[1]:      " << address_of(pc + 1) << "\n";
        std::cout << "Address of ps[1]:      " << address_of(ps + 1) << "\n\n";

        std::cout << "Address of circles[3]: " << address_of(circles + 3) << "\n";
        std::cout << "Address of pc[3]:      " << address_of(pc + 3) << "\n";
        std::cout << "Address of ps[3]:      " << address_of(ps + 3) << "\n\n";

        std::cout << "Size of Circle:        " << sizeof(Circle) << "\n";
        std::cout << "Size of Shape:         " << sizeof(Shape) << "\n\n";
    }
}

} // namespace pointers
