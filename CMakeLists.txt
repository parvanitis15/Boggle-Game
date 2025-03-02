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
    
    # Add optimization flags for Release builds
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(
            /O2     # Maximize speed
            /Ob2    # Inline function expansion
            /GL     # Whole program optimization
            /DNDEBUG # Define NDEBUG macro
        )
    endif()
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
    
    # Add optimization flags for Release builds
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(
            -O3        # Highest level of optimization
            -DNDEBUG   # Define NDEBUG macro
            -march=native # Optimize for the current CPU architecture
        )
    endif()
endif()

# Set build type to Debug by default if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Print configuration information during build
message(STATUS "Building in ${CMAKE_BUILD_TYPE} mode")
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")

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

# Create benchmark executable
add_executable(boggle_benchmark
    tests/test_boggle_benchmark.cpp
    src/board/Board.cpp
    src/trie/Node.cpp
    src/trie/Trie.cpp
    src/algorithm/VisitMap.cpp
    src/algorithm/boggle_algorithm.cpp
)

# Add include directories for all targets
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

target_include_directories(boggle_benchmark PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/board
    ${CMAKE_SOURCE_DIR}/src/trie
    ${CMAKE_SOURCE_DIR}/src/algorithm
    ${CMAKE_SOURCE_DIR}/src/verification
    ${CMAKE_SOURCE_DIR}/tests
    ${GTEST_INCLUDE_DIRS}
)

# Link Google Test to the test executables
target_link_libraries(boggle_tests PRIVATE GTest::GTest GTest::Main)
target_link_libraries(boggle_benchmark PRIVATE GTest::GTest GTest::Main)

# Add the tests to CTest
add_test(NAME boggle_tests COMMAND boggle_tests)
add_test(NAME boggle_benchmark COMMAND boggle_benchmark)

# Print a message about running the benchmark
message(STATUS "To run the benchmark in release mode, use the run_benchmark script")
