cmake_minimum_required (VERSION 3.20)


add_library("compile_time_eval_lib")

target_sources("compile_time_eval_lib"
    PUBLIC
    "include/compile_time_eval.hpp"
    "include/auto_parameters.hpp"
    "include/concepts.hpp"
    "include/function_templates.hpp"
    "include/class_templates.hpp" "include/nontype_templates.hpp")

target_sources("compile_time_eval_lib"
    PRIVATE
    "src/compile_time_eval.cpp" "src/class_templates.cpp")

target_include_directories("compile_time_eval_lib"
    PUBLIC
    "include")

target_link_libraries("compile_time_eval_lib"
    "GSL")


add_executable ("compile_time_eval")

target_sources("compile_time_eval" PRIVATE
    "src/compile_time_eval_main.cpp")

target_link_libraries("compile_time_eval"
    "GSL"
	"compile_time_eval_lib")

add_subdirectory(test)
