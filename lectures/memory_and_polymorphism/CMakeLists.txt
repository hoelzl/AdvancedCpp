cmake_minimum_required (VERSION 3.21)
project(MemoryAndPolymorphism)

set(CMAKE_CXX_STANDARD 20)
set(MEMORY_SOURCES
        "memory_main.cpp"
        "print_memory_layout.cpp"
        "print_memory_layout.h"
        "polymorphic_array.h")

add_executable (pam_simple "simple.cpp")
add_executable (pam_memory ${MEMORY_SOURCES})
add_executable (pam_polymorphism "polymorphism_main.cpp" "animal.h" "dog.h" "cat.h")
add_executable (pam_copy_move "copy_move_main.cpp" "animal.h" "dog.h" "cat.h")
