#pragma once

#include "LRU.h"

namespace caches {

template<typename T, typename KeyT = int>
class cache_2q {
    size_t a1_sz_;
public:
    cache_lru<T, KeyT> am_;
    std::list<std::pair<KeyT, T> > a1_cache_;
    using ListIt = typename std::list<std::pair<KeyT, T> >::iterator;
    std::unordered_map<KeyT, ListIt> a1_hash_;

    cache_2q(const size_t size_am, const size_t size_a1) : am_(size_am), a1_sz_(size_a1) {};

    bool full() const { return (a1_cache_.size() == a1_sz_); }

    template<typename F>
    bool lookup_update(KeyT key, F slow_get_page) {
        // Search in AM cache
        auto hit_am = am_.hash_.find(key);
        if (hit_am != am_.hash_.end()) {
            am_.move_to_front(hit_am->second);
            return true;
        }
        // Search in A1 queue
        auto hit_a1 = a1_hash_.find(key);
        if (hit_a1 == a1_hash_.end()) {
            if (full()) {
                a1_hash_.erase(a1_cache_.front().first);
                a1_cache_.pop_front();
            }
            a1_cache_.emplace_back(key, slow_get_page(key));
            auto it = std::prev(a1_cache_.end());
            a1_hash_.emplace(key, it);
            return false;
        }
        // Move from A1 queue to AM cache
        if (am_.full()) {
            am_.remove_from_back();
        }
        am_.add_front(key, slow_get_page);
        a1_cache_.erase(hit_a1->second);
        a1_hash_.erase(hit_a1);
        return true;
    }
};
}