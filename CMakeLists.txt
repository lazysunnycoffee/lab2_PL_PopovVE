cmake_minimum_required(VERSION 3.10)
project(Ccryptarithm C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)


set(SOLVER_SOURCES src/solver.c)

add_executable(cryptarithm src/main.c ${SOLVER_SOURCES})

add_executable(test_runner test/test.c ${SOLVER_SOURCES})

add_executable(bench_runner bench/bench.c ${SOLVER_SOURCES})
