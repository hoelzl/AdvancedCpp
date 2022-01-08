cmake_minimum_required (VERSION 3.21)


add_library("solutions_lib")

target_sources("solutions_lib"
    PUBLIC
    "include/solutions.hpp")

target_sources("solutions_lib"
    PRIVATE
    "src/solutions.cpp")

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
