cmake_minimum_required(VERSION 3.10)
project(TinyLRUCache)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# TinyLRU Library
add_library(tinylru
    src/lru_cache.cpp
    src/lru_cache_read_optimized.cpp
)

target_include_directories(tinylru PUBLIC include)

# Example binary
add_executable(tiny_lru_example
    src/main.cpp
)

target_link_libraries(tiny_lru_example tinylru)

# Benchmark binary
add_executable(tiny_lru_benchmark
    benchmarks/benchmark.cpp
)

target_link_libraries(tiny_lru_benchmark tinylru pthread)

# Unit tests binary
add_executable(tiny_lru_tests
    tests/test_lru.cpp
)

target_link_libraries(tiny_lru_tests tinylru pthread)
