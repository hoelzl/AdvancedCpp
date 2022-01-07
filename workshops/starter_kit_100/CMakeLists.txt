cmake_minimum_required (VERSION 3.21)


add_library("starter_kit_100_lib")

target_sources("starter_kit_100_lib"
    PUBLIC
    "include/starter_kit_100.hpp")

target_sources("starter_kit_100_lib"
    PRIVATE
    "src/starter_kit_100.cpp")

target_include_directories("starter_kit_100_lib"
    PUBLIC 
    "include")

target_link_libraries("starter_kit_100_lib"
    "GSL")


add_executable ("starter_kit_100")

target_sources("starter_kit_100" PRIVATE
    "src/starter_kit_100_main.cpp")

target_link_libraries("starter_kit_100"
    "GSL"
	"starter_kit_100_lib")

add_subdirectory(test)
