# Tiny LRU Cache (C++)

A lightweight, high-performance, thread-safe LRU cache implemented in modern C++.  
Includes:

- Standard thread-safe LRU Cache (`mutex`)
- Read-optimized LRU Cache (`shared_mutex`)
- Full OOP design (encapsulation, inheritance, polymorphism)
- Benchmarks for hit/miss ratio + throughput under multithreading
- Unit tests

---

## 🚀 Features

### ✔ Standard LRU Cache
- Uses `unordered_map` + doubly-linked list
- Thread-safe using `std::mutex`
- O(1) get + put

### ✔ Read-Optimized LRU Cache
- Uses `std::shared_mutex`
- Multiple concurrent readers
- ~30%+ faster in read-heavy workloads

### ✔ Clean OOP Architecture
- `LRUBase` — abstract base interface
- `LRUCache` — standard thread-safe cache
- `LRUCacheReadOptimized` — shared-mutex optimized version

---

## 📦 Project Structure
- include/ # Header files
- src/ # Implementation
- benchmarks/ # Benchmark tests
- tests/ # Unit tests
- CMakeLists.txt # Build configuration

## 🛠 Build Instructions

### Build (Linux/macOS/Windows)
mkdir build
cd build
cmake ..
make -j8

### Run Tests
./tiny_lru_example

### Run BenchMark
./tiny_lru_tests



