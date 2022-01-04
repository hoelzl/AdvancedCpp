add_executable("operators_test")

target_sources("operators_test" PRIVATE
    "operators_test.cpp"
 "hidden_friends_test.cpp" "operators_cpp20_test.cpp")

target_link_libraries("operators_test"
    "Catch2WithMain"
	"operators_lib"
)