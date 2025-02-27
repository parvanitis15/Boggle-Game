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

# # Enable testing
# enable_testing()

# # Find GTest package
# find_package(GTest REQUIRED)

# Create executable from your source files
add_executable(boggle_solver
    src/main.cpp
    src/Board.cpp
    src/Node.cpp
    src/Trie.cpp
    src/VisitMap.cpp
    src/boggle_algorithm.cpp
    src/boggle_tester.cpp
)

# Add include directories
target_include_directories(boggle_solver PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/tests
)

# Set output directory to match your current setup
set_target_properties(boggle_solver
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
) 

# # Add the test to CTest
# add_test(NAME boggle_tests COMMAND boggle_tests)
