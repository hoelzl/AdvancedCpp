add_executable("starter_kit_test")

target_sources("starter_kit_test" PRIVATE
    "starter_kit_test.cpp"
 "tic_tac_toe_test.cpp")

target_link_libraries("starter_kit_test"
    "Catch2WithMain"
	"starter_kit_lib"
)