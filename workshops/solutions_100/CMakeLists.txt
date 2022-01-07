cmake_minimum_required (VERSION 3.21)


add_library("solutions_100_lib")

target_sources("solutions_100_lib"
    PUBLIC
    "include/solutions_100.hpp")

target_sources("solutions_100_lib"
    PRIVATE
    "src/solutions_100.cpp")

target_include_directories("solutions_100_lib"
    PUBLIC 
    "include")

target_link_libraries("solutions_100_lib"
    "GSL")


add_executable ("solutions_100")

target_sources("solutions_100" PRIVATE
    "src/solutions_100_main.cpp")

target_link_libraries("solutions_100"
    "GSL"
	"solutions_100_lib")

add_subdirectory(test)
