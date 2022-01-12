add_executable("concurrency_test")

target_sources("concurrency_test" PRIVATE
    "concurrency_test.cpp"
)

target_link_libraries("concurrency_test"
    "Catch2WithMain"
	"concurrency_lib"
)