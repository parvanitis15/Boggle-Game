cmake_minimum_required(VERSION 3.10)
project(BoggleSolver CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler flags to match your current settings
add_compile_options(
    -pedantic-errors
    -Wall
    -Weffc++
    -Wextra
    -Wconversion
    -Wsign-conversion
    -Werror
)

# Add debug symbols
set(CMAKE_BUILD_TYPE Debug)

# Enable testing
enable_testing()

# Find GTest package
find_package(GTest REQUIRED)
include(GoogleTest)

# Create main executable
add_executable(boggle_solver
    src/main.cpp
    src/Board.cpp
    src/Node.cpp
    src/Trie.cpp
    src/VisitMap.cpp
    src/boggle_algorithm.cpp
    src/boggle_tester.cpp
)

# Create test executables
add_executable(boggle_tests
    tests/test_boggle.cpp
    tests/test_boggle_performance.cpp
    src/Board.cpp
    src/Node.cpp
    src/Trie.cpp
    src/VisitMap.cpp
    src/boggle_algorithm.cpp
)

# Add include directories for both targets
target_include_directories(boggle_solver PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_include_directories(boggle_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/tests
    ${GTEST_INCLUDE_DIRS}
)

# Link Google Test to the test executable
target_link_libraries(boggle_tests PRIVATE GTest::GTest GTest::Main)

# Set output directory for both executables
set_target_properties(boggle_solver boggle_tests
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

# Add the test to CTest
add_test(NAME boggle_tests COMMAND boggle_tests)
