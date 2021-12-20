#include "array_dangers.hpp"

#include <iostream>

namespace pointers {

void circle::draw() const
{
    std::cout.precision(1);
    std::cout << "Drawing circle at " << x() << ", " << y() << ".\n";    
}

} // namespace pointers
