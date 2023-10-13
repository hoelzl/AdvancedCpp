cmake_minimum_required (VERSION 3.20)


add_library("resources_lib")

target_sources("resources_lib"
    PUBLIC
    "include/resources.hpp")

target_sources("resources_lib"
    PRIVATE
    "src/resources.cpp")

target_include_directories("resources_lib"
    PUBLIC
    "include")

target_link_libraries("resources_lib"
    "GSL")


add_executable ("resources")

target_sources("resources" PRIVATE
    "src/resources_main.cpp")

target_link_libraries("resources"
    "GSL"
	"resources_lib")

add_subdirectory(test)
