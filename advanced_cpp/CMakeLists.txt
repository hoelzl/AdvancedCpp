cmake_minimum_required (VERSION 3.21)

add_executable ("advanced-cpp")

target_sources("advanced-cpp" PRIVATE
    "src/advanced_cpp.cpp" "include/advanced_cpp.hpp")

target_include_directories("advanced-cpp" PUBLIC include)

add_subdirectory(test)