cmake_minimum_required(VERSION 3.16)
project(MatrixProject)

set(CMAKE_CXX_STANDARD 17)

# Tu ejecutable principal (ejemplo interactivo)
add_executable(MatrixMain example.cpp Matrix.h)

# Agregamos GoogleTest
add_subdirectory(external/googletest)
enable_testing()

# Subdirectorio de tests
add_subdirectory(tests)
