#pragma once

#include<iostream>
#include <iterator>
#include <list>
#include <unordered_map>

namespace caches {

// Implemented 2Q algorithm: https://arpitbhayani.me/blogs/2q-cache/

struct cache_2q_utils {

const static int mult_num = 2;
const static int mult_denum = 5;

};


template<typename T, typename KeyT = int>
class cache_2q {
public:
    using ListIt = typename std::list<std::pair<KeyT, T> >::iterator;
    std::list<std::pair<KeyT, T> > cache_hot_;
    std::unordered_map<KeyT, ListIt> hash_hot_;
    std::list<std::pair<KeyT, T> > cache_cold_;
    std::unordered_map<KeyT, ListIt> hash_cold_;

    cache_2q(const size_t size): hot_sz_(size * cache_2q_utils::mult_num / cache_2q_utils::mult_denum),
                                 cold_sz_(size - size * cache_2q_utils::mult_num / cache_2q_utils::mult_denum) {};

    template<typename F>
    bool lookup_update(const KeyT key, F slow_get_page) {
        // Search in hot lru cache
        const auto hit_hot = hash_hot_.find(key);
        if (hit_hot != hash_hot_.end()) {
            const auto eltit = hit_hot->second;
            if (eltit != cache_hot_.begin())
                cache_hot_.splice(cache_hot_.begin(), cache_hot_, eltit, std::next(eltit));
            return true;
        }
        // Search in cold queue
        const auto hit_cold = hash_cold_.find(key);
        if (hit_cold == hash_cold_.end()) {
            if (full_cold()) {
                hash_cold_.erase(cache_cold_.front().first);
                cache_cold_.pop_front();
            }
            cache_cold_.emplace_back(key, slow_get_page(key));
            auto it = std::prev(cache_cold_.end());
            hash_cold_.emplace(key, it);
            return false;
        }
        // Move from cold queue to hot cache
        if (full_hot()) {
            hash_hot_.erase(cache_hot_.back().first);
            cache_hot_.pop_back();
        }
        cache_hot_.emplace_front(key, slow_get_page(key));
        hash_hot_.emplace(key, cache_hot_.begin());
        cache_cold_.erase(hit_cold->second);
        hash_cold_.erase(hit_cold);
        return true;
    }

private:
    bool full_hot() const { return (cache_hot_.size() == hot_sz_); }
    bool full_cold() const { return (cache_cold_.size() == cold_sz_); }

private:
    size_t hot_sz_;
    size_t cold_sz_;
};
}
