add_executable("imgui_example_test")

target_sources("imgui_example_test" PRIVATE
    "imgui_example_test.cpp"
)

target_link_libraries("imgui_example_test"
    "Catch2WithMain"
	"imgui_example_lib"
)