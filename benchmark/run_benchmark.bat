@echo off
echo Boggle Benchmark Runner

REM Create build directory if it doesn't exist
if not exist benchmark_build mkdir benchmark_build

REM Try to build with Visual Studio first
echo Attempting to build with Visual Studio...
cd benchmark_build

REM Configure with CMake for Visual Studio
cmake .. -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=Release
if %ERRORLEVEL% EQU 0 (
    REM Build the benchmark
    cmake --build . --config Release
    
    REM Check if the build was successful
    if %ERRORLEVEL% EQU 0 (
        set BENCHMARK_EXE=Release\boggle_benchmark.exe
        cd ..
        goto RUN_BENCHMARK
    )
)

REM If Visual Studio build failed, try MinGW
echo Visual Studio build failed or not available, trying MinGW...
cd ..

REM Create MinGW build directory if it doesn't exist
if not exist mingw_build mkdir mingw_build
cd mingw_build

REM Configure with CMake for MinGW
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
if %ERRORLEVEL% NEQ 0 (
    echo CMake configuration with MinGW failed.
    cd ..
    exit /b 1
)

REM Build the benchmark with MinGW
cmake --build .
if %ERRORLEVEL% NEQ 0 (
    echo MinGW build failed.
    cd ..
    exit /b 1
)

set BENCHMARK_EXE=boggle_benchmark.exe
cd ..

:RUN_BENCHMARK
echo.
echo Running Boggle Benchmark...
echo.

REM Check if the benchmark executable exists
if exist "benchmark_build\%BENCHMARK_EXE%" (
    benchmark_build\%BENCHMARK_EXE%
) else if exist "mingw_build\%BENCHMARK_EXE%" (
    mingw_build\%BENCHMARK_EXE%
) else (
    echo Benchmark executable not found. Build may have failed.
    exit /b 1
)

echo.
echo Benchmark completed.
