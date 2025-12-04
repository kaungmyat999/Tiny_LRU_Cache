#pragma once
#include <unordered_map>

template <typename K, typename V>
struct Node {
    K key;
    V value;
    Node* prev;
    Node* next;
    Node(K k, V v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

template <typename K, typename V>
class LRUBase {
public:
    virtual bool get(const K& key, V& out) = 0;
    virtual void put(const K& key, const V& value) = 0;
    virtual ~LRUBase() = default;
};
