cmake_minimum_required(VERSION 3.10)
project(Ccryptarithm C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()
set(CMAKE_C_FLAGS_DEBUG   "-O0 -g")
set(CMAKE_C_FLAGS_RELEASE "-O2 -g")   

add_compile_options(-Wall -Wextra)

set(SOLVER_SOURCES src/solver.c)

add_executable(cryptarithm src/main.c ${SOLVER_SOURCES})
add_executable(test_runner test/test.c ${SOLVER_SOURCES})
add_executable(bench_runner bench/bench.c ${SOLVER_SOURCES})

enable_testing()
add_test(NAME solver_tests COMMAND test_runner)