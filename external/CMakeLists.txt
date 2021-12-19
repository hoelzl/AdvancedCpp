add_library(doctest INTERFACE "doctest/doctest.hpp")
target_include_directories(doctest INTERFACE "doctest")

add_subdirectory(gsl)
