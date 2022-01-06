cmake_minimum_required (VERSION 3.21)

set(CMAKE_CXX_STANDARD 23)

add_library("constexpr_lib")

target_sources("constexpr_lib"
    PUBLIC
    "include/constexpr_demo.hpp" "include/consteval_demo.hpp")

target_sources("constexpr_lib"
    PRIVATE
    "src/constexpr_demo.cpp")

target_include_directories("constexpr_lib"
    PUBLIC 
    "include")

target_link_libraries("constexpr_lib"
    "GSL")


add_executable ("constexpr")

target_sources("constexpr" PRIVATE
    "src/constexpr_main.cpp")

target_link_libraries("constexpr"
    "GSL"
	"constexpr_lib")

add_subdirectory(test)
