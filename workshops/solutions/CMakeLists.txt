cmake_minimum_required (VERSION 3.21)


add_library("solutions_lib")

target_sources("solutions_lib"
    PUBLIC
    "include/solutions.hpp" "include/ring_buffer.hpp" "include/int_range.hpp" "include/templates.hpp" "include/pair.hpp")

target_sources("solutions_lib"
    PRIVATE
    "src/solutions.cpp" "src/ring_buffer.cpp" "src/int_range.cpp")

target_include_directories("solutions_lib"
    PUBLIC 
    "include")

target_link_libraries("solutions_lib"
    "GSL")


add_executable ("solutions")

target_sources("solutions" PRIVATE
    "src/solutions_main.cpp")

target_link_libraries("solutions"
    "GSL"
	"solutions_lib")

add_subdirectory(test)
