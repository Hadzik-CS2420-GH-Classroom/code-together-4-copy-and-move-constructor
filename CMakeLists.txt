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

# Source files (excluding main.cpp so tests can provide their own entry point)
set(LIB_SOURCES
    src/Bio.cpp
    src/NameTag.cpp
    src/FancyNameTag.cpp
)

# Create an executable target from the listed source files
add_executable(${PROJECT_NAME}
    src/main.cpp
    ${LIB_SOURCES}
)

# Tell the compiler where to find our header files
target_include_directories(${PROJECT_NAME} PRIVATE include)

# ==================== Google Test ====================
# Fetch GoogleTest from GitHub so we don't need it installed locally
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable CMake's built-in test runner (ctest)
enable_testing()

# Test executable — links against gtest_main so we don't need our own main()
add_executable(run_tests
    tests/copy_move_test.cpp
    ${LIB_SOURCES}
)

target_include_directories(run_tests
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(run_tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(run_tests)
