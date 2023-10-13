cmake_minimum_required (VERSION 3.20)

set(CMAKE_CXX_STANDARD 23)

add_library("rpg_dice_lib")

target_sources("rpg_dice_lib"
    PUBLIC
    "include/rpg_dice.hpp")

target_sources("rpg_dice_lib"
    PRIVATE
    "src/rpg_dice.cpp")

target_include_directories("rpg_dice_lib"
    PUBLIC
    "include")

target_link_libraries("rpg_dice_lib"
    "GSL")


add_executable ("rpg_dice")

target_sources("rpg_dice" PRIVATE
    "src/rpg_dice_main.cpp")

target_link_libraries("rpg_dice"
    "GSL"
	"rpg_dice_lib")

add_subdirectory(test)
