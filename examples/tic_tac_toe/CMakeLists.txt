cmake_minimum_required (VERSION 3.20)


set(CMAKE_CXX_STANDARD 23)

add_library("tic_tac_toe_lib")

target_sources("tic_tac_toe_lib"
    PUBLIC
    "include/tic_tac_toe.hpp")

target_sources("tic_tac_toe_lib"
    PRIVATE
    "src/tic_tac_toe.cpp")

target_include_directories("tic_tac_toe_lib"
    PUBLIC
    "include")

target_link_libraries("tic_tac_toe_lib"
    "GSL")


add_executable ("tic_tac_toe")

target_sources("tic_tac_toe" PRIVATE
    "src/tic_tac_toe_main.cpp")

target_link_libraries("tic_tac_toe"
    "GSL"
	"tic_tac_toe_lib")

add_subdirectory(test)
