cmake_minimum_required (VERSION 3.21)


add_library("stl_lib")

target_sources("stl_lib"
    PUBLIC
    "include/stl.hpp" "include/type_erasure.hpp" "include/repeated_vector_wrapper.hpp")

target_sources("stl_lib"
    PRIVATE
    "src/stl.cpp" "src/repeated_vector_wrapper.cpp")

target_include_directories("stl_lib"
    PUBLIC 
    "include")

target_link_libraries("stl_lib"
    "GSL")


add_executable ("stl")

target_sources("stl" PRIVATE
    "src/stl_main.cpp")

target_link_libraries("stl"
    "GSL"
	"stl_lib")

add_subdirectory(test)
