cmake_minimum_required(VERSION 3.16)
project(Sudoku VERSION 1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define the executable target and its source files
add_executable(sudoku
	src/main.cpp
	src/sudoku.cpp
)

# Specify include directories
target_include_directories(sudoku PRIVATE include)

# Compiler-specific warning flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(sudoku PRIVATE -Wall -Wextra -Wpedantic -O3)
endif()
