#include <gtest/gtest.h>
cmake -S . -B build
cmake --build build
ctest --test-dir b
