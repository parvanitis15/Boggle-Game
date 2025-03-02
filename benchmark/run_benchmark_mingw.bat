@echo off
echo Building Boggle Benchmark in Release mode with MinGW...

:: Create build directory if it doesn't exist
if not exist benchmark_build_mingw mkdir benchmark_build_mingw

:: Navigate to build directory
cd benchmark_build_mingw

:: Configure with CMake in Release mode using MinGW
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..

:: Build the benchmark
cmake --build . --config Release

:: Run the benchmark
echo.
echo Running Boggle Benchmark...
echo.

:: Check if the executable exists
if exist boggle_benchmark.exe (
    boggle_benchmark.exe
) else (
    echo Benchmark executable not found. Build may have failed.
    exit /b 1
)

:: Return to original directory
cd ..

echo.
echo Benchmark completed.
pause 
