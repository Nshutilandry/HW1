#include <gtest/gtest.h>
make_minimum_required(VERSION 3.20)
project(hw1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Warnings and runtime checks for every target in this project.
# AddressSanitizer reports out-of-bounds access and memory leaks;
# UndefinedBehaviorSanitizer reports signed overflow and similar.
add_compile_options(-Wall -Wextra -Wpedantic -fsanitize=address,undefined -fno-omit-frame-pointer)
add_link_options(-fsanitize=address,undefined)

# Everything except main() lives in a library so the tests can link to it.
# Add each new .cpp file to this list.
add_library(hw1_lib
    src/station.cpp
    src/grid.cpp
    src/analysis.cpp
    src/report.cpp
)
target_include_directories(hw1_lib PUBLIC include)

add_executable(hw1 src/main.cpp)
target_link_libraries(hw1 PRIVATE hw1_lib)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.2
)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_executable(hw1_tests tests/test_hw1.cpp)
target_link_libraries(hw1_tests PRIVATE hw1_lib GTest::gtest_main)
gtest_discover_tests(hw1_tests)
