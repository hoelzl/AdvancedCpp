add_executable("advanced-cpp-test")

target_sources("advanced-cpp-test" PRIVATE
    "advanced_cpp_test.cpp")

target_link_libraries("advanced-cpp-test" "Catch2WithMain" "advanced-cpp-lib")