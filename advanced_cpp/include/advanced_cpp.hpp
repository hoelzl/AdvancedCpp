#pragma once

#include <iostream>

inline void write_greeting(std::string_view const name)
{
    std::cout << "Hello " << name << ", from the advanced C++ course.\n";
}
