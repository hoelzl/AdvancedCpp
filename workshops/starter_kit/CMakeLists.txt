cmake_minimum_required (VERSION 3.20)


add_library("starter_kit_lib")

target_sources("starter_kit_lib"
    PUBLIC
    "include/starter_kit.hpp")

target_sources("starter_kit_lib"
    PRIVATE
    "src/starter_kit.cpp")

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

add_subdirectory(test)
