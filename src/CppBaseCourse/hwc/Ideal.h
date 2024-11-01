#pragma once

#include <unordered_map>
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

namespace caches {

class cache_ideal {

    size_t sz_;
    std::unordered_map<int, int> cache_;

public:

    cache_ideal(const size_t sz) : sz_(sz) {};

    int lookup_update(const std::vector<int>& keys_seq) {
        int hits = 0;
        const size_t seq_size = keys_seq.size();
        std::cout << "Ideal cache running ...!" << std::endl;

        std::unordered_map<int, std::queue<int>> map_of_indexes;

        index_mapping(map_of_indexes, keys_seq);

        for (size_t i = 0; i < seq_size; ++i) {
            int value = keys_seq[i];
            if (!map_of_indexes[value].empty()) {
                map_of_indexes[value].pop();
            }
            if (cache_.find(value) != cache_.end()) {
                ++hits;
                continue;
            }
            if (!full()) {
                cache_[value] = 0; 
            } else {
                int curr_elem = find_farthest(value, map_of_indexes);

                if (curr_elem == value) {
                    continue;
                }
                cache_.erase(curr_elem);
                cache_[value] = 0; 
            }
        }

        return hits;
    }

private:

    bool full() const { return cache_.size() == sz_; }

    int find_farthest(int value, std::unordered_map<int, std::queue<int>>& map_of_indexes) {
        int farthest_ind = -1;
        int farthest_elem;

        for (auto it = cache_.begin(); it != cache_.end(); ++it) {
            int curr_elem = it->first;
            std::queue<int> curr_list = map_of_indexes[curr_elem];

            if (curr_list.empty()) {
                return curr_elem;
            }

            if (curr_list.front() > farthest_ind) {
                farthest_ind = curr_list.front();
                farthest_elem = curr_elem;
            }
        }
        
        const std::queue<int> new_elem_list = map_of_indexes[value];

        if (new_elem_list.empty() || new_elem_list.front() > farthest_ind) {
            return value;
        }

        return farthest_elem;
    }

    void index_mapping(std::unordered_map<int, std::queue<int>>& map_of_indexes, const std::vector<int>& keys_seq) {
        const size_t elems_size = keys_seq.size();
        for (int i = 0; i < elems_size; ++i) {
            if (map_of_indexes.find(keys_seq[i]) == map_of_indexes.end())
                map_of_indexes[keys_seq[i]] = std::queue<int>();

            map_of_indexes[keys_seq[i]].push(i);
        }
    }

};

}  // namespace caches
