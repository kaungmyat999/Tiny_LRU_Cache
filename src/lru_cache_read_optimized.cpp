#include "lru_cache_read_optimized.h"
#include <mutex>

template <typename K, typename V>
LRUCacheReadOptimized<K,V>::LRUCacheReadOptimized(size_t cap)
    : capacity(cap), head(nullptr), tail(nullptr) {}

template <typename K, typename V>
void LRUCacheReadOptimized<K,V>::moveToFront(Node<K,V>* node) {
    if (node == head) return;

    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;
    if (node == tail) tail = node->prev;

    node->prev = nullptr;
    node->next = head;
    head->prev = node;
    head = node;
}

template <typename K, typename V>
void LRUCacheReadOptimized<K,V>::evict() {
    map.erase(tail->key);
    auto prev = tail->prev;
    if (prev) prev->next = nullptr;
    delete tail;
    tail = prev;
}

template <typename K, typename V>
bool LRUCacheReadOptimized<K,V>::get(const K& key, V& out) {
    std::shared_lock read(rwlock);

    if (!map.count(key)) return false;

    auto node = map[key];
    out = node->value;

    read.unlock();
    std::unique_lock write(rwlock);
    moveToFront(node);

    return true;
}

template <typename K, typename V>
void LRUCacheReadOptimized<K,V>::put(const K& key, const V& value) {
    std::unique_lock write(rwlock);

    if (map.count(key)) {
        auto node = map[key];
        node->value = value;
        moveToFront(node);
        return;
    }

    Node<K,V>* node = new Node<K,V>(key, value);
    map[key] = node;

    if (!head) head = tail = node;
    else {
        node->next = head;
        head->prev = node;
        head = node;
    }

    if (map.size() > capacity)
        evict();
}

// Explicit instantiation
template class LRUCacheReadOptimized<int,int>;

