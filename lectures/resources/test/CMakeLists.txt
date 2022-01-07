add_executable("resources_test")

target_sources("resources_test" PRIVATE
    "resources_test.cpp"
)

target_link_libraries("resources_test"
    "Catch2WithMain"
	"resources_lib"
)