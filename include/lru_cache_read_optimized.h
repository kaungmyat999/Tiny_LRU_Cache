#pragma once
#include "lru_base.h"
#include <unordered_map>
#include <shared_mutex>

template <typename K, typename V>
class LRUCacheReadOptimized : public LRUBase<K,V> {
public:
    explicit LRUCacheReadOptimized(size_t capacity);

    bool get(const K& key, V& out) override;
    void put(const K& key, const V& value) override;

private:
    size_t capacity;
    std::unordered_map<K, Node<K,V>*> map;
    Node<K,V>* head;
    Node<K,V>* tail;

    mutable std::shared_mutex rwlock;

    void moveToFront(Node<K,V>* node);
    void evict();
};

