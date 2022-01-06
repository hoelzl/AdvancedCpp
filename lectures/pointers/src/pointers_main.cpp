#include <iostream>
#include <sstream>

#include "array_dangers.hpp"
#include "pointers.hpp"

using namespace pointers;
using namespace std::ranges;

int main()  // NOLINT(bugprone-exception-escape)
{
    try {
        show_pointer_operations();

        std::cout << "\n\n" << std::string(72, '*') << "\n\n";
        pointers::show_bad_array_signatures();

        std::cout << "\n\n" << std::string(72, '*') << "\n\n";
        pointers::show_bad_array_access();
    }
    catch (...) {
        std::cerr << "Oops...\n";
    }
}
