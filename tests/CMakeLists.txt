cmake_minimum_required(VERSION 3.12)

project(tests)


find_package(GTest REQUIRED)

add_executable( runUnitTests 
elementary_operations_test.cpp
helpers.cpp
helpers.hpp
)

target_link_libraries(runUnitTests
 gtest gtest_main  ImageProc)

add_test( runUnitTests runUnitTests)
