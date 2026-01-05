cmake_minimum_required(VERSION 3.14)
project(NES_Emulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB CPU_SOURCES 
    "src/CPU/main.cpp"
    "src/CPU/*.cpp"
    "src/CPU/instructions/*.cpp"
    "src/Memory/*.cpp"
)

message(STATUS "CPU Sources found: ${CPU_SOURCES}")
add_library(emulator_lib ${CPU_SOURCES})

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB TEST_FILES 
    "tests/*.cpp"
    "tests/instructions/*.cpp"
)

add_executable(unit_tests ${TEST_FILES})

target_link_libraries(unit_tests
    PRIVATE emulator_lib
    PRIVATE gtest_main
)

include(GoogleTest)
gtest_discover_tests(unit_tests)
