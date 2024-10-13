#pragma once

#include <list>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <optional>

namespace caches {

template<typename T, typename KeyT = int>
class cache_ideal {

    size_t sz_;

public:
    using ListIt = typename std::list<std::pair<KeyT, T> >::iterator;
    std::list<std::pair<KeyT, T> > cache_;
    std::unordered_map<KeyT, ListIt> hash_;

    cache_ideal(const size_t sz) : sz_(sz) {}

    bool full() const { return (cache_.size() == sz_); }

    template<typename F>
    bool lookup_update(const KeyT key, F slow_get_page, const std::vector<KeyT> &future_refs, const int current_pos) {
        const auto hit = hash_.find(key);

        if (hit == hash_.end()) {
            if (full()) {
                auto key_to_evict = evict(future_refs, current_pos, key);
                if (!key_to_evict.has_value()) {
                    slow_get_page(key);
                    return false;
                }
                if (auto remove_it = hash_.find(key_to_evict.value()); remove_it != hash_.end()) {
                    cache_.erase(remove_it->second);
                    hash_.erase(remove_it);
                }
            }
            cache_.emplace_front(key, slow_get_page(key));
            hash_.emplace(key, cache_.begin());
            return false;
        }

        return true;
    }

private:

    std::optional<KeyT> evict(const std::vector<KeyT> &future_refs, const int current_pos, const KeyT new_key) {
        KeyT key_to_evict;
        KeyT cached_key;
        int farthest_in_future = -1;
        int next_occurrence = -1;

        for (const auto &item: cache_) {
            cached_key = item.first;
            next_occurrence = find_next_occurrence(future_refs, cached_key, current_pos);

            if (next_occurrence == -1) {
                key_to_evict = cached_key;
                break;
            }
            if (next_occurrence > farthest_in_future) {
                farthest_in_future = next_occurrence;
                key_to_evict = cached_key;
            }
        }
        const int new_elem_next_occ = find_next_occurrence(future_refs, new_key, current_pos);

        if(new_elem_next_occ > farthest_in_future || new_elem_next_occ == -1) {
            return std::nullopt;
        }
        return key_to_evict;
    }

    int find_next_occurrence(const std::vector<KeyT> &future_refs, const KeyT key, const int current_pos) {
        const int future_ref_size = future_refs.size();
        for (int i = current_pos + 1; i < future_ref_size; ++i) {
            if (future_refs[i] == key) {
                return i;
            }
        }
        return -1;
    }
};

}
