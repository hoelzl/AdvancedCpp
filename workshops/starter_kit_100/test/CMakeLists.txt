add_executable("starter_kit_100_test")

target_sources("starter_kit_100_test" PRIVATE
    "starter_kit_100_test.cpp"
)

target_link_libraries("starter_kit_100_test"
    "Catch2WithMain"
	"starter_kit_100_lib"
)