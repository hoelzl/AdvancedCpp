cmake_minimum_required (VERSION 3.21)


add_library("rpg_dice_sk_lib")

target_sources("rpg_dice_sk_lib"
    PUBLIC
    "include/rpg_dice_sk.hpp")

target_sources("rpg_dice_sk_lib"
    PRIVATE
    "src/rpg_dice_sk.cpp")

target_include_directories("rpg_dice_sk_lib"
    PUBLIC 
    "include")

target_link_libraries("rpg_dice_sk_lib"
    "GSL")


add_executable ("rpg_dice_sk")

target_sources("rpg_dice_sk" PRIVATE
    "src/rpg_dice_sk_main.cpp")

target_link_libraries("rpg_dice_sk"
    "GSL"
	"rpg_dice_sk_lib")

add_subdirectory(test)
