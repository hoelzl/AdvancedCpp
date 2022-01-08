add_executable("solutions_100_test")

target_sources("solutions_100_test" PRIVATE
    "solutions_100_test.cpp"
)

target_link_libraries("solutions_100_test"
    "Catch2WithMain"
	"solutions_100_lib"
)
