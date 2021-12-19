cmake_minimum_required (VERSION 3.21)

add_library("advanced-cpp-lib")

target_sources("advanced-cpp-lib" PUBLIC
    "include/advanced_cpp.hpp")
target_sources("advanced-cpp-lib" PRIVATE
    "src/advanced_cpp.cpp")
target_include_directories("advanced-cpp-lib" PUBLIC include)
target_link_libraries("advanced-cpp-lib" "GSL")


add_executable ("advanced-cpp")

target_sources("advanced-cpp" PRIVATE
    "src/advanced_cpp_main.cpp")

target_link_libraries("advanced-cpp" "GSL" "advanced-cpp-lib")

add_subdirectory(test)