add_executable("compile_time_eval_test")

target_sources("compile_time_eval_test" PRIVATE
    "compile_time_eval_test.cpp"
    "auto_parameters_test.cpp" "concepts_test.cpp" "function_templates_test.cpp" "class_templates_test.cpp" "nontype_templates.cpp")

target_link_libraries("compile_time_eval_test"
    "Catch2WithMain"
	"compile_time_eval_lib"
)