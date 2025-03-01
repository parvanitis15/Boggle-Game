# Boggle Game Solver

[![C++ CI](https://github.com/parvanitis15/Boggle-Game/actions/workflows/ci.yml/badge.svg)](https://github.com/parvanitis15/Boggle-Game/actions/workflows/ci.yml)
[![Code Quality](https://github.com/parvanitis15/Boggle-Game/actions/workflows/code-quality.yml/badge.svg)](https://github.com/parvanitis15/Boggle-Game/actions/workflows/code-quality.yml)
[![Release](https://github.com/parvanitis15/Boggle-Game/actions/workflows/release.yml/badge.svg)](https://github.com/parvanitis15/Boggle-Game/actions/workflows/release.yml)

A C++ implementation of a Boggle word search algorithm. This repository contains C++ code to solve the board game: Boggle. It implements algorithms and data structures suitable for the problem, with efficiency and safety in mind.

## Features

- Fast word search using Trie data structure
- Two implementation approaches: recursive and iterative
- Comprehensive test suite with Google Test
- Performance benchmarks for various board sizes

## How It Works

### Boggle Algorithm

The Boggle solver finds all valid words in a Boggle board by traversing the board and checking if the formed words exist in a dictionary. The core algorithm works as follows:

1. Build a Trie data structure from a dictionary of valid words
2. For each cell in the Boggle board:
   - Start a traversal from that cell
   - Explore all adjacent cells (horizontally, vertically, and diagonally)
   - Track visited cells to avoid using the same cell twice in a word
   - Check if the current path forms a valid word in the Trie
   - If valid, add it to the list of found words

### Implementation Approaches

#### Recursive Approach

The recursive implementation uses depth-first search with backtracking:

- For each starting position, a recursive function explores all possible paths
- Each recursive call represents moving to an adjacent cell
- The recursion naturally handles the backtracking when a path doesn't lead to valid words
- Parameters are passed by value to maintain separate state for each path

Benefits:
- Clean, intuitive implementation
- Efficient memory usage for the call stack
- Typically faster performance

#### Iterative Approach

The iterative implementation uses explicit stacks to simulate recursion:

- Maintains stacks for row indices, column indices, current words, visited cells, and direction indices
- Manually manages the state that would be handled by the call stack in the recursive approach
- Uses a loop to process the stacks until they're empty

Benefits:
- Avoids potential stack overflow for very large boards
- More explicit control over the traversal process
- Can be more memory efficient for extremely deep traversals

### Performance Comparison

Performance tests show that the recursive approach is generally faster than the iterative approach, typically by a factor of 2x. This is likely due to the overhead of managing multiple stacks in the iterative approach.

## Testing Framework

The project includes a comprehensive testing framework with two main test suites:

### Functional Tests (`test_boggle.cpp`)

- Validates the correctness of both recursive and iterative algorithms
- Ensures both algorithms find the expected words in a predefined board
- Verifies that both algorithms produce identical results

### Performance Tests (`test_boggle_performance.cpp`)

- Measures and compares the performance of both algorithms across different board sizes:
  - Small (4x4)
  - Medium (8x8)
  - Large (16x16)
  - Huge (32x32)
- Tests with both basic and extended word lists
- Automatically verifies that both algorithms find the same number of words
- Enforces performance constraints (timeout of 1 second)

The performance tests are designed to be modular, allowing easy addition of new algorithms or board sizes for comparison.

## Building the Project

### Prerequisites

- CMake 3.10 or higher
- C++17 compatible compiler
- Google Test

### Build Instructions

```bash
mkdir build
cd build
cmake ..
make
```

## Running Tests

```bash
cd build
ctest
```

Or run the test executable directly:

```bash
./boggle_tests
```

## CI/CD Pipeline

This project uses GitHub Actions for continuous integration and deployment:

1. **CI Workflow**: Builds and tests the code on multiple platforms (Linux, macOS, Windows)
2. **Code Quality**: Checks code formatting and performs static analysis
3. **Release**: Creates releases with binaries for multiple platforms when a tag is pushed

## Creating a Release

To create a new release:

```bash
git tag v1.0.0
git push origin v1.0.0
```

This will trigger the release workflow, which will build the project and upload the binaries to the GitHub release.

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE.txt](LICENSE.txt) file for details. 
