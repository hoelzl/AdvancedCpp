cmake_minimum_required (VERSION 3.21)


add_library("pointers_lib")

target_sources("pointers_lib"
    PUBLIC
    "include/pointers.hpp")

target_sources("pointers_lib"
    PRIVATE
    "src/pointers.cpp")

target_include_directories("pointers_lib"
    PUBLIC 
    "include")

target_link_libraries("pointers_lib"
    "GSL")


add_executable ("pointers")

target_sources("pointers" PRIVATE
    "src/pointers_main.cpp")

target_link_libraries("pointers"
    "GSL"
	"pointers_lib")

add_subdirectory(test)
