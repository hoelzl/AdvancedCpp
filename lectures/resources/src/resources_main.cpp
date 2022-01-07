// ReSharper disable CppClangTidyCppcoreguidelinesAvoidCArrays
// ReSharper disable CppClangTidyBugproneExceptionEscape
#include "resources.hpp"
#include <iostream>

int main()
{
	res::write_greeting("world");

	// Don't do this...
	int array_of_ints[] = {1, 2, 3, 4, 5};
	// ... but if you have to, define the called function using a gsl::span that
	// encapsulates the array and its length.
	std::cout << "Here is some number: " << res::add_ints(array_of_ints) << ".\n";

	return 0;
}
