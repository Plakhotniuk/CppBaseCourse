#pragma once

#include "LRU.h"
#include <queue>

namespace caches {

template<typename T, typename KeyT = int>
struct cache_2q {
private:
    cache_lru<T, KeyT> am_;
    std::list<std::pair<KeyT, T>> a1_cache_;
    using ListIt = typename std::list<std::pair<KeyT, T>>::iterator;
    std::unordered_map<KeyT, ListIt> a1_hash_;

    size_t a1_sz_;

public:

    cache_2q(const size_t size_am, const size_t size_a1) : am_(size_am), a1_sz_(size_a1) {};

    bool full() const { return (a1_cache_.size() == a1_sz_); }

    template<typename F>
    bool lookup_update(KeyT key, F slow_get_page) {
        if (am_.lookup_update(key, slow_get_page)) {
            return true;
        }
        auto hit = a1_hash_.find(key);
        if (hit == a1_hash_.end()) {
            if(full()){
                // If A1 cache is full, remove the least recently used (LRU) item
                a1_hash_.erase(a1_cache_.front().first);
                a1_cache_.pop_front();  // Remove LRU from A1 cache
            }
            // Add the new item to the A1 cache
            a1_cache_.emplace_back(key, slow_get_page(key));
            auto it = std::prev(a1_cache_.end());  // Get iterator to the last element
            a1_hash_.emplace(key, it);  // Store the iterator in the hash map
            return false;  // Cache miss
        }

        if (am_.full()) {
            am_.hash_.erase(am_.cache_.back().first);
            am_.cache_.pop_back();
        }
        am_.cache_.emplace_front(key, hit->second->second);
        am_.hash_.emplace(key, am_.cache_.begin());
        a1_hash_.erase(hit);
        a1_cache_.erase(hit->second);
        return true;
    }
};
}
