cmake_minimum_required(VERSION 3.10)

# Project Name
project(RayTracing)

# Use C++11 to match the "In One Weekend" requirements
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define the executable
# This creates an executable named "RayTracing" from "src/main.cpp"
add_executable(RayTracing src/main.cpp)

# This helps the compiler find header files (like vec3.h) inside 'src'
# when you add them later
target_include_directories(RayTracing PUBLIC src)