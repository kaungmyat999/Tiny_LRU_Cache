#include "lru_cache.h"

template <typename K, typename V>
LRUCache<K,V>::LRUCache(size_t cap) : capacity(cap), head(nullptr), tail(nullptr) {}

template <typename K, typename V>
void LRUCache<K,V>::moveToFront(Node<K,V>* node) {
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
void LRUCache<K,V>::evict() {
    map.erase(tail->key);

    auto prev = tail->prev;
    if (prev) prev->next = nullptr;
    delete tail;
    tail = prev;
}

template <typename K, typename V>
bool LRUCache<K,V>::get(const K& key, V& out) {
    std::lock_guard<std::mutex> lock(mtx);

    if (!map.count(key)) return false;

    auto node = map[key];
    out = node->value;
    moveToFront(node);
    return true;
}

template <typename K, typename V>
void LRUCache<K,V>::put(const K& key, const V& value) {
    std::lock_guard<std::mutex> lock(mtx);

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

// Explicit template instantiation
template class LRUCache<int,int>;

