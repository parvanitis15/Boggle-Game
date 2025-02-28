# Boggle Game Solver

[![C++ CI](https://github.com/parvanitis15/Boggle-Game/actions/workflows/ci.yml/badge.svg)](https://github.com/parvanitis15/Boggle-Game/actions/workflows/ci.yml)
<!-- [![Code Quality](https://github.com/parvanitis15/Boggle-Game/actions/workflows/code-quality.yml/badge.svg)](https://github.com/parvanitis15/Boggle-Game/actions/workflows/code-quality.yml) -->
<!-- [![Release](https://github.com/parvanitis15/Boggle-Game/actions/workflows/release.yml/badge.svg)](https://github.com/parvanitis15/Boggle-Game/actions/workflows/release.yml) -->

A C++ implementation of a Boggle word search algorithm. This repository contains C++ code to solve the board game: Boggle. It implements algorithms and data structures suitable for the problem, with efficiency and safety in mind.

## Features

- Fast word search using Trie data structure
- Comprehensive test suite with Google Test
- Performance benchmarks for various board sizes

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
<!-- 3. **Release**: Creates releases with binaries for multiple platforms when a tag is pushed -->

## Creating a Release

To create a new release:

```bash
git tag v1.0.0
git push origin v1.0.0
```

This will trigger the release workflow, which will build the project and upload the binaries to the GitHub release.

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE.txt](LICENSE.txt) file for details. 
