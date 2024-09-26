#pragma once

#include "LRU.h"

namespace caches {
// Implemented 2Q algorithm: https://arpitbhayani.me/blogs/2q-cache/
template<typename T, typename KeyT = int>
class cache_2q {

    size_t a1_sz_;

public:
    cache_lru<T, KeyT> am_;
    std::list<std::pair<KeyT, T> > a1_cache_;
    using ListIt = typename std::list<std::pair<KeyT, T> >::iterator;
    std::unordered_map<KeyT, ListIt> a1_hash_;

    cache_2q(const size_t size) : am_(size), a1_sz_(size) {};

    bool full() const { return (a1_cache_.size() == a1_sz_); }

    template<typename F>
    bool lookup_update(const KeyT key, F slow_get_page) {
        // Search in AM cache
        const auto hit_am = am_.hash_.find(key);
        if (hit_am != am_.hash_.end()) {
            const auto eltit = hit_am->second;
            if (eltit != am_.cache_.begin())
                am_.cache_.splice(am_.cache_.begin(), am_.cache_, eltit, std::next(eltit));
            return true;
        }
        // Search in A1 queue
        const auto hit_a1 = a1_hash_.find(key);
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
            am_.hash_.erase(am_.cache_.back().first);
            am_.cache_.pop_back();
        }
        am_.cache_.emplace_front(key, slow_get_page(key));
        am_.hash_.emplace(key, am_.cache_.begin());
        a1_cache_.erase(hit_a1->second);
        a1_hash_.erase(hit_a1);
        return true;
    }
};
}
