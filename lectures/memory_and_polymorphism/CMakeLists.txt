cmake_minimum_required (VERSION 3.21)
project(MemoryAndPolymorphism)

set(CMAKE_CXX_STANDARD 20)
set(MEMORY_SOURCES
        "memory_main.cpp"
        "print_memory_layout.cpp"
        "print_memory_layout.hpp"
        "polymorphic_array.hpp")

option(ASAN_ENABLED "Build all targets with AddressSanitizer" OFF)

add_executable (pam_simple "simple.cpp")
target_link_libraries(pam_simple "GSL")
add_executable (pam_memory ${MEMORY_SOURCES})
target_link_libraries(pam_memory "GSL")
add_executable (pam_polymorphism "polymorphism_main.cpp" "animal.hpp" "dog.hpp" "cat.hpp")
target_link_libraries(pam_polymorphism "GSL")
add_executable (pam_copy_move "copy_move_main.cpp" "animal.hpp" "dog.hpp" "cat.hpp")
target_link_libraries(pam_copy_move "GSL")

if(ASAN_ENABLED)
  if(MSVC)
    target_compile_options(pam_simple PUBLIC /fsanitize=address)
    target_compile_options(pam_memory PUBLIC /fsanitize=address)
    target_compile_options(pam_polymorphism PUBLIC /fsanitize=address)
    target_compile_options(pam_copy_move PUBLIC /fsanitize=address)
  else()
    target_compile_options(pam_simple PUBLIC -fsanitize=address)
    target_link_options(pam_simple PUBLIC -fsanitize=address)
    target_compile_options(pam_memory PUBLIC -fsanitize=address)
    target_link_options(pam_memory PUBLIC -fsanitize=address)
    target_compile_options(pam_polymorphism PUBLIC -fsanitize=address)
    target_link_options(pam_polymorphism PUBLIC -fsanitize=address)
    target_compile_options(pam_copy_move PUBLIC -fsanitize=address)
    target_link_options(pam_copy_move PUBLIC -fsanitize=address)
  endif()
endif()
