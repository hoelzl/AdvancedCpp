cmake_minimum_required (VERSION 3.20)


add_library("concurrency_lib")

target_sources("concurrency_lib"
    PUBLIC
    "include/concurrency.hpp")

target_sources("concurrency_lib"
    PRIVATE
    "src/concurrency.cpp")

target_include_directories("concurrency_lib"
    PUBLIC
    "include")

target_link_libraries("concurrency_lib"
    "GSL")


add_executable ("concurrency")

target_sources("concurrency" PRIVATE
    "src/concurrency_main.cpp")

target_link_libraries("concurrency"
    "GSL"
	"concurrency_lib")

add_subdirectory(test)
