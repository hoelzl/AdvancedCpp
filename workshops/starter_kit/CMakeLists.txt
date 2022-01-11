cmake_minimum_required (VERSION 3.21)

set(CMAKE_CXX_STANDARD 23)

add_library("starter_kit_lib")

target_sources("starter_kit_lib"
    PUBLIC
    "include/starter_kit.hpp" "include/tic_tac_toe.hpp")

target_sources("starter_kit_lib"
    PRIVATE
    "src/starter_kit.cpp" "src/tic_tac_toe.cpp")

target_include_directories("starter_kit_lib"
    PUBLIC 
    "include")

target_link_libraries("starter_kit_lib"
    "GSL")


add_executable ("starter_kit")

target_sources("starter_kit" PRIVATE
    "src/starter_kit_main.cpp")

target_link_libraries("starter_kit"
    "GSL"
	"starter_kit_lib")

add_executable ("tic_tac_toe_v2")

target_sources("tic_tac_toe_v2" PRIVATE
    "src/tic_tac_toe_main.cpp")

target_link_libraries("tic_tac_toe_v2"
    "GSL"
	"starter_kit_lib")

add_subdirectory(test)
