#include "lru_cache.h"
#include <cassert>
#include <iostream>

int main() {
    LRUCache<int,int> cache(2);

    cache.put(1,100);
    cache.put(2,200);

    int value;
    assert(cache.get(1, value) && value == 100);

    cache.put(3,300); // evicts 2

    assert(!cache.get(2, value));
    assert(cache.get(3, value));

    std::cout << "All tests passed!\n";
    return 0;
}

