cmake_minimum_required (VERSION 3.20)


add_library("variants_lib")

target_sources("variants_lib"
    PUBLIC
    "include/variants.hpp")

target_sources("variants_lib"
    PRIVATE
    "src/variants.cpp")

target_include_directories("variants_lib"
    PUBLIC
    "include")

target_link_libraries("variants_lib"
    "GSL")


add_executable ("variants")

target_sources("variants" PRIVATE
    "src/variants_main.cpp")

target_link_libraries("variants"
    "GSL"
	"variants_lib")

add_subdirectory(test)
