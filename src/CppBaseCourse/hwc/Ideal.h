#pragma once

#include <unordered_map>
#include <vector>
#include <algorithm>
#include <span>

namespace caches {

template<typename KeyT = int>
class cache_ideal {

    size_t sz_;
    std::vector<std::pair<KeyT, int> > dist_;

public:
    using VecIt = typename std::vector<std::pair<KeyT, int> >::iterator;
    std::unordered_map<KeyT, VecIt> dist_hash_;

    cache_ideal(const size_t sz) : sz_(sz) {
        dist_.reserve(sz);
    }

    bool full() const { return dist_.size() == sz_; }

    template<typename F>
    int lookup_update(F slow_get_page, std::span<const KeyT> keys_seq) {
        int hits_count = 0;
        const size_t seq_size = keys_seq.size();
        int max_dist = seq_size;

        for (size_t i = 0; i < seq_size; ++i) {

            // Update the distances of cached items
            for (auto& n : dist_) {
                --n.second;
            }

            auto hit = dist_hash_.find(keys_seq[i]);

            const int next_occ = find_next_occurrence(keys_seq.subspan(i + 1, seq_size - i - 1), keys_seq[i], seq_size);
            auto farthest_it = std::max_element(dist_.begin(), dist_.end(), CompareByDist{});
            max_dist = farthest_it->second;

            if (hit == dist_hash_.end()) {

                if (full()) {
                    if (next_occ > farthest_it->second) { continue; }

                    dist_hash_.erase(farthest_it->first);
                    dist_.erase(farthest_it);
                }

                dist_.emplace_back(keys_seq[i], next_occ);
                dist_hash_[keys_seq[i]] = std::prev(dist_.end()); 
            } else {
                ++hits_count;
                hit->second->second = next_occ;
            }
        }

        return hits_count;
    }

private:
    // Find the next occurrence of the key in the future sequence
    int find_next_occurrence(std::span<const KeyT> future_refs, const KeyT key, int max_size) {
        int distance = 0;
        for (const auto& elem : future_refs) {
            if (elem == key) {
                return distance;
            }
            ++distance;
        }
        return max_size;
    }

    struct CompareByDist {
        bool operator()(const std::pair<KeyT, int>& a, const std::pair<KeyT, int>& b) const {
            return a.second < b.second;
        }
    };
};

}  // namespace caches
