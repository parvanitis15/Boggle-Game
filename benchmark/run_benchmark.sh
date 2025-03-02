#!/bin/bash

echo "Building Boggle Benchmark in Release mode..."

# Create build directory if it doesn't exist
mkdir -p benchmark_build

# Navigate to build directory
cd benchmark_build

# Configure with CMake in Release mode
cmake -DCMAKE_BUILD_TYPE=Release ..

# Build the benchmark
cmake --build . --config Release

# Run the benchmark
echo ""
echo "Running Boggle Benchmark..."
echo ""

# Check if the executable exists
if [ -f "./boggle_benchmark" ]; then
    ./boggle_benchmark
elif [ -f "./Release/boggle_benchmark" ]; then
    ./Release/boggle_benchmark
else
    echo "Benchmark executable not found. Build may have failed."
    exit 1
fi

# Return to original directory
cd ..

echo ""
echo "Benchmark completed." 
