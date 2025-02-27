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

# Create executable from your source files
add_executable(boggle_solver
    main.cpp
    Board.cpp
    Node.cpp
    Trie.cpp
    VisitMap.cpp
    boggle_algorithm.cpp
    boggle_tester.cpp
)

# Set output directory to match your current setup
set_target_properties(boggle_solver
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}"
) 
