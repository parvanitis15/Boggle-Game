cmake_minimum_required(VERSION 3.10)
project(BoggleSolver CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler flags based on compiler type
if(MSVC)
    # MSVC (Visual Studio) compiler flags
    add_compile_options(
        /W4     # Warning level 4
        /WX     # Treat warnings as errors
        /EHsc   # Enable C++ exceptions
        /permissive-  # Enforce standards conformance
    )
else()
    # GCC/Clang compiler flags
    add_compile_options(
        -pedantic-errors
        -Wall
        -Weffc++
        -Wextra
        -Wconversion
        -Wsign-conversion
        -Werror
    )
endif()

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
    src/board/Board.cpp
    src/trie/Node.cpp
    src/trie/Trie.cpp
    src/algorithm/VisitMap.cpp
    src/algorithm/boggle_algorithm.cpp
    src/verification/boggle_tester.cpp
)

# Create test executables
add_executable(boggle_tests
    tests/test_boggle.cpp
    tests/test_boggle_performance.cpp
    src/board/Board.cpp
    src/trie/Node.cpp
    src/trie/Trie.cpp
    src/algorithm/VisitMap.cpp
    src/algorithm/boggle_algorithm.cpp
)

# Add include directories for both targets
target_include_directories(boggle_solver PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/board
    ${CMAKE_SOURCE_DIR}/src/trie
    ${CMAKE_SOURCE_DIR}/src/algorithm
    ${CMAKE_SOURCE_DIR}/src/verification
)

target_include_directories(boggle_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/board
    ${CMAKE_SOURCE_DIR}/src/trie
    ${CMAKE_SOURCE_DIR}/src/algorithm
    ${CMAKE_SOURCE_DIR}/src/verification
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
