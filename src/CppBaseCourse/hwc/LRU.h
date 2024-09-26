#pragma once

#include <iterator>
#include <list>
#include <unordered_map>

namespace caches {

template<typename T, typename KeyT = int>
class cache_lru {

    size_t sz_;

public:
    using ListIt = typename std::list<std::pair<KeyT, T> >::iterator;
    std::list<std::pair<KeyT, T> > cache_;
    std::unordered_map<KeyT, ListIt> hash_;

    cache_lru(const size_t sz) : sz_(sz) {}

    bool full() const { return (cache_.size() == sz_); }

    template<typename F>
    bool lookup_update(const KeyT key, F slow_get_page) {
        const auto hit = hash_.find(key);
        if (hit == hash_.end()) {
            if (full()) {
                hash_.erase(cache_.back().first);
                cache_.pop_back();
            }
            cache_.emplace_front(key, slow_get_page(key));
            hash_.emplace(key, cache_.begin());
            return false;
        }

        const ListIt eltit = hit->second;
        if (eltit != cache_.begin())
            cache_.splice(cache_.begin(), cache_, eltit, std::next(eltit));
        return true;
    }
};
}
