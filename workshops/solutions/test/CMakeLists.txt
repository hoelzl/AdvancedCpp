add_executable("solutions_test")

target_sources("solutions_test" PRIVATE
    "solutions_test.cpp"
 "ring_buffer_test.cpp" "int_range_test.cpp" "templates_test.cpp")

target_link_libraries("solutions_test"
    "Catch2WithMain"
	"solutions_lib"
)
