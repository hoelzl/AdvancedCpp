cmake_minimum_required (VERSION 3.21)


add_library("imgui_example_lib")

target_sources("imgui_example_lib"
    PUBLIC
    "include/imgui_example.hpp")

target_sources("imgui_example_lib"
    PRIVATE
    "src/imgui_example.cpp")

target_include_directories("imgui_example_lib"
    PUBLIC 
    "include")

target_link_libraries("imgui_example_lib"
    "GSL"
    "ImFrame")


add_executable ("imgui_example" WIN32)

target_sources("imgui_example" PRIVATE
    "src/imgui_example_main.cpp")

target_link_libraries("imgui_example"
    "GSL"
	"imgui_example_lib")

if(MSVC)
	target_compile_options("imgui_example" PRIVATE /W4 /WX)
else()
	target_compile_options("imgui_example" PRIVATE -Wall -Wextra -pedantic -Werror)
endif()


add_subdirectory(test)
