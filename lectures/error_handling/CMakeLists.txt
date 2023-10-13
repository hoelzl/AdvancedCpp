cmake_minimum_required (VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)

add_library("error_handling_lib")

target_sources("error_handling_lib"
    PUBLIC
    "error_code_with_query/error_code_with_query.hpp"
    "global_error_code/global_error_code.hpp"
    "throw_only/throw_only.hpp"
    "try_catch/try_catch.hpp"
    "types_expected/types_expected.hpp"
)

target_sources("error_handling_lib"
    PRIVATE
    "error_code_with_query/error_code_with_query.cpp"
    "global_error_code/global_error_code.cpp"
    "throw_only/throw_only.cpp"
    "try_catch/try_catch.cpp"
    "types_expected/types_expected.cpp"
)

add_executable("error_handling_test")

target_sources("error_handling_test"
    PRIVATE
    "error_code_with_query/error_code_with_query_test.cpp"
    "global_error_code/global_error_code_test.cpp"
    "throw_only/throw_only_test.cpp"
    "try_catch/try_catch_test.cpp"
    "types_expected/types_expected_test.cpp"
)

target_link_libraries("error_handling_test"
    "Catch2WithMain"
    "error_handling_lib")