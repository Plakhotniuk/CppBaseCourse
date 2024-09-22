#pragma once

#include <iterator>
#include <list>
#include <unordered_map>

namespace caches {

template<typename T, typename KeyT = int>
class cache_lru {
    size_t sz_;
public:
    std::list<std::pair<KeyT, T> > cache_;
    using ListIt = typename std::list<std::pair<KeyT, T> >::iterator;
    std::unordered_map<KeyT, ListIt> hash_;

    cache_lru(size_t sz) : sz_(sz) {}

    bool full() const { return (cache_.size() == sz_); }

    template<typename F>
    void add_front(KeyT key, F slow_get_page) {
        cache_.emplace_front(key, slow_get_page(key));
        hash_.emplace(key, cache_.begin());
    }

    void remove_from_back() {
        hash_.erase(cache_.back().first);
        cache_.pop_back();
    }

    void move_to_front(ListIt eltit){
        if (eltit != cache_.begin())
            cache_.splice(cache_.begin(), cache_, eltit, std::next(eltit));
    }

    template<typename F>
    bool lookup_update(KeyT key, F slow_get_page) {
        auto hit = hash_.find(key);
        if (hit == hash_.end()) {
            if (full()) {
                remove_from_back();
            }
            add_front(key, slow_get_page);
            return false;
        }

        move_to_front(hit->second);
        return true;
    }
};
}
