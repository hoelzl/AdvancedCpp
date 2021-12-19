#include "advanced_cpp.hpp"
#include <iostream>

int main()
{
	write_greeting("world");

	// Don't do this...
	int array_of_ints[] = {1, 2, 3, 4, 5};
	std::cout << "Here is some number: " << add_ints(array_of_ints) << "\n";

	return 0;
}
