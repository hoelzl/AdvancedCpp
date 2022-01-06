cmake_minimum_required (VERSION 3.21)


add_library("operators_lib")

target_sources("operators_lib"
    PUBLIC
    "include/operators.hpp" "include/hidden_friends.hpp" "include/operators_cpp20.hpp")

target_sources("operators_lib"
    PRIVATE
    "src/operators.cpp" "src/hidden_friends.cpp")

target_include_directories("operators_lib"
    PUBLIC 
    "include")

target_link_libraries("operators_lib"
    "GSL")


add_executable ("operators")

target_sources("operators" PRIVATE
    "src/operators_main.cpp")

target_link_libraries("operators"
    "GSL"
	"operators_lib")

add_subdirectory(test)
