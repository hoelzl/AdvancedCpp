# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.21)

project ("AdvancedCpp")

set(CMAKE_CXX_STANDARD 20)

add_subdirectory ("advanced_cpp")
add_subdirectory ("external")
