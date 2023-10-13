cmake_minimum_required (VERSION 3.20)


add_library("advanced_cpp_lib")

target_sources("advanced_cpp_lib"
    PUBLIC
    "include/advanced_cpp.hpp")

target_sources("advanced_cpp_lib"
    PRIVATE
    "src/advanced_cpp.cpp")

target_include_directories("advanced_cpp_lib"
    PUBLIC
    "include")

target_link_libraries("advanced_cpp_lib"
    "GSL")


add_executable ("advanced_cpp")

target_sources("advanced_cpp" PRIVATE
    "src/advanced_cpp_main.cpp")

target_link_libraries("advanced_cpp"
    "GSL"
	"advanced_cpp_lib")

add_subdirectory(test)
