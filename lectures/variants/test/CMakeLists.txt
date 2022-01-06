add_executable("variants_test")

target_sources("variants_test" PRIVATE
    "variants_test.cpp"
)

target_link_libraries("variants_test"
    "Catch2WithMain"
	"variants_lib"
)