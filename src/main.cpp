#include "lru_cache.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>   

template <typename K, typename V>
void printCache(LRUCache<K,V>& cache, const std::vector<K>& keys) {
    std::cout << "Current cache keys: ";
    for (const auto& k : keys) std::cout << k << " ";
    std::cout << "\n";
}

int main() {
    std::srand(std::time(nullptr));

    LRUCache<int,int> cache(3); // capacity 3
    std::vector<int> currentKeys; // track inserted keys

    for (int i = 0; i < 10; i++) {
        int key = std::rand() % 5;   // keys from 0-4
        int value = std::rand() % 100;

        cache.put(key, value);

        // track current keys for printing (naive)
        if (std::find(currentKeys.begin(), currentKeys.end(), key) == currentKeys.end()) {
            if (currentKeys.size() >= 3) currentKeys.erase(currentKeys.begin());
            currentKeys.push_back(key);
        }

        std::cout << "Put " << key << "=" << value << "\n";

        int getKey = std::rand() % 5;
        int out;
        if (cache.get(getKey, out))
            std::cout << "Get " << getKey << " -> Hit: " << out << "\n";
        else
            std::cout << "Get " << getKey << " -> Miss\n";

        printCache(cache, currentKeys);
        std::cout << "---------------------------\n";
    }

    return 0;
}
