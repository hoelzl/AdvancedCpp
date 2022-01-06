add_executable("tic_tac_toe_test")

target_sources("tic_tac_toe_test" PRIVATE
    "tic_tac_toe_test.cpp"
)

target_link_libraries("tic_tac_toe_test"
    "Catch2WithMain"
	"tic_tac_toe_lib"
)