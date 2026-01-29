# Minimum CMake version required to build this project
cmake_minimum_required(VERSION 3.20)
# Define the project name and specify C++ as the language
project(CopyAndMoveConstructor LANGUAGES CXX)

# Use C++20 standard
set(CMAKE_CXX_STANDARD 20)
# Require the specified standard (fail if not supported)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Disable compiler-specific extensions for portability
set(CMAKE_CXX_EXTENSIONS OFF)

# Create an executable target from the listed source files
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Bio.cpp
    src/NameTag.cpp
    src/FancyNameTag.cpp
)

# Tell the compiler where to find our header files
target_include_directories(${PROJECT_NAME} PRIVATE include)
