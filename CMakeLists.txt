﻿# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.20)

project ("AdvancedCpp")

set(CMAKE_CXX_STANDARD 20)

add_subdirectory("external")
add_subdirectory("examples")
add_subdirectory("lectures")
add_subdirectory("workshops")
