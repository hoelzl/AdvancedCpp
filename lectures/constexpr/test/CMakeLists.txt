add_executable("constexpr_test")

target_sources("constexpr_test" PRIVATE
    "constexpr_test.cpp"
)

target_link_libraries("constexpr_test"
    "Catch2WithMain"
	"constexpr_lib"
)