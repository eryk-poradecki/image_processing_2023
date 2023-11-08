cmake_minimum_required(VERSION 3.12)
project(tests)

if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    ### MACOS
    include_directories(/usr/local/include)
    link_directories(/usr/local/lib)
    ###
endif()

find_package(GTest REQUIRED)

add_executable( runUnitTests
elementary_operations_test.cpp
helpers.cpp
helpers.hpp
geometric_operations_test.cpp
analysis_operation_test.cpp
noise_removal_test.cpp
histogram_test.cpp
img_characteristics_test.cpp
)

target_link_libraries(runUnitTests gtest gtest_main ImageProc)

add_test(runUnitTests runUnitTests)
