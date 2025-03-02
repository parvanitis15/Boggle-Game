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
- The algorithm marks cells as visited before exploring and unmarks them when backtracking
- A shared `VisitMap` tracks visited cells for each starting position

Benefits:
- Clean, intuitive implementation
- Efficient memory usage for the call stack
- Typically faster for most board sizes

#### Iterative Approach

The iterative implementation uses an explicit stack to simulate recursion:

- Uses a `SearchState` structure to track the current row, column, direction index, and word
- Maintains a stack of these states to simulate the call stack
- Systematically explores all 8 possible directions from each cell
- Explicitly manages backtracking by incrementing the direction index and popping from the stack
- Uses a shared `VisitMap` for efficient tracking of visited cells

Benefits:
- Avoids potential stack overflow for very large boards
- More explicit control over the traversal process
- Can be more memory efficient for extremely deep traversals

### Performance Comparison

Based on sample benchmark results for a 32x32 board with the extended word list:

```
Performance comparison:
  Recursive mean time: 3960 microseconds
  Iterative mean time: 4045 microseconds
  Ratio (Recursive/Iterative): 0.98
  Recursive algorithm is 2.10% faster
```

However, performance can vary significantly depending on:
- Hardware specifications
- Compiler and optimization settings
- Operating system
- Board size and word list complexity

**Important**: You should run the benchmark on your own system to get accurate performance metrics. The benchmark scripts in the `benchmark` directory will automatically:
- Build the project with optimizations enabled
- Run multiple iterations to ensure statistical significance
- Calculate the performance ratio between algorithms
- Determine which algorithm performs better on your specific configuration

The performance difference between recursive and iterative approaches is often small (as shown in the sample results above), but can vary based on your specific environment.

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

## Benchmarks

The Boggle Solver includes a comprehensive benchmarking system to measure and compare the performance of different solving algorithms. The benchmarks help evaluate the efficiency of the recursive and iterative approaches on a large 32x32 board with an extended word list.

### Running Benchmarks

Benchmarks are located in the `benchmark` directory and can be run using the provided scripts:

- **Linux/macOS**: Use `./benchmark/run_benchmark.sh`
- **Windows**: Use `benchmark/run_benchmark.bat` (MSVC) or `benchmark/run_benchmark_mingw.bat` for MinGW

These scripts will:
1. Build the project in Release mode with optimizations enabled
2. Run the benchmark tests
3. Display detailed performance metrics

### Benchmark Features

The benchmarking system:

- Measures execution time in microseconds using high-resolution clock
- Runs multiple iterations (default: 10) to calculate mean execution time
- Compares recursive vs. iterative algorithm performance
- Calculates performance ratios and percentage differences
- Verifies that both algorithms find the same number of valid words
- Tests with a challenging 32x32 board and extended word list to stress-test the algorithms

### Sample Benchmark Output

```
Running 10 iterations for Recursive algorithm on Huge Board (32x32) with Extended Word List...
  Iteration 1: 12345 microseconds
  Iteration 2: 12300 microseconds
  ...

Results for Recursive algorithm:
  Board size: 32x32
  Mean execution time: 12320 microseconds
  Words found: 1234

Performance comparison:
  Recursive mean time: 12320 microseconds
  Iterative mean time: 10240 microseconds
  Ratio (Recursive/Iterative): 1.20
  Iterative algorithm is 20% faster
```

### Customizing Benchmarks

You can modify the benchmark parameters in `tests/test_boggle_benchmark.cpp` to:
- Change the number of iterations
- Adjust the board size
- Use different word lists
- Add new algorithm implementations

For optimal results, always run benchmarks in Release mode to ensure compiler optimizations are applied.

## Creating a Release

To create a new release:

```bash
git tag v1.0.0
git push origin v1.0.0
```

This will trigger the release workflow, which will build the project and upload the binaries to the GitHub release.

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE.txt](LICENSE.txt) file for details. 
