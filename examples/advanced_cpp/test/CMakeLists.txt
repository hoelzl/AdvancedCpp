add_executable("advanced_cpp_test")

target_sources("advanced_cpp_test" PRIVATE
    "advanced_cpp_test.cpp"
)

target_link_libraries("advanced_cpp_test"
    "Catch2WithMain"
	"advanced_cpp_lib"
)