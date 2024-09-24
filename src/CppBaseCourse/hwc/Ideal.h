#pragma once

#include <list>
#include <unordered_map>
#include <vector>
#include <algorithm>

namespace caches {

template<typename T, typename KeyT = int>
class cache_ideal {
    size_t sz_;  // Cache size

public:
    std::list<std::pair<KeyT, T> > cache_;
    using ListIt = typename std::list<std::pair<KeyT, T> >::iterator;
    std::unordered_map<KeyT, ListIt> hash_;

    cache_ideal(size_t sz) : sz_(sz) {}

    bool full() const { return (cache_.size() == sz_); }

    void move_to_front(ListIt eltit){
        if (eltit != cache_.begin())
            cache_.splice(cache_.begin(), cache_, eltit, std::next(eltit));
    }

    void remove_elem(KeyT key)
    {
        auto remove_it = hash_.find(key);
        if (remove_it != hash_.end()) {
            cache_.erase(remove_it->second);
            hash_.erase(remove_it);
        }
    }

    template<typename F>
    bool lookup_update(KeyT key, F slow_get_page, const std::vector<KeyT> &future_refs, int current_pos) {
        auto hit = hash_.find(key);

        if (hit == hash_.end()) {
            if (full()) {
                evict(future_refs, current_pos);
            }
            cache_.emplace_front(key, slow_get_page(key));
            hash_.emplace(key, cache_.begin());
            return false;
        }

        move_to_front(hit->second);
        return true;
    }

private:

    void evict(const std::vector<KeyT> &future_refs, int current_pos) {
        KeyT key_to_evict;
        int farthest_in_future = -1;

        for (const auto &item: cache_) {
            KeyT cached_key = item.first;
            int next_occurrence = find_next_occurrence(future_refs, cached_key, current_pos);

            if (next_occurrence == -1)
            {
                key_to_evict = cached_key;
                break;
            }
            if (next_occurrence > farthest_in_future) {
                farthest_in_future = next_occurrence;
                key_to_evict = cached_key;
            }
        }

        remove_elem(key_to_evict);
    }

    int find_next_occurrence(const std::vector<KeyT> &future_refs, KeyT key, int current_pos) {
        for (int i = current_pos + 1; i < future_refs.size(); ++i) {
            if (future_refs[i] == key) {
                return i;
            }
        }
        return -1;
    }
};

}
