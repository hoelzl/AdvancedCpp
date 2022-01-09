add_executable("stl_test")

target_sources("stl_test" PRIVATE
    "stl_test.cpp"
 "type_erasure_test.cpp")

target_link_libraries("stl_test"
    "Catch2WithMain"
	"stl_lib"
)