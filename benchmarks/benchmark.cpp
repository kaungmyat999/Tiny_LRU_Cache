#include "lru_cache_read_optimized.h"
#include <thread>
#include <vector>
#include <chrono>
#include <iostream>

int main() {
    LRUCacheReadOptimized<int,int> cache(1000);

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> workers;
    for (int t = 0; t < 8; t++) {
        workers.emplace_back([&]() {
            for (int i = 0; i < 500000; i++) {
                int v;
                cache.get(i % 500, v);
                cache.put(i % 500, i);
            }
        });
    }

    for (auto& w : workers) w.join();

    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "Finished in "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    return 0;
}

