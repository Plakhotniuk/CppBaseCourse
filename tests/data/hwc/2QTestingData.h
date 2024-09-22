#pragma once

#include <vector>

namespace cache_2q_testing {
// slow get page imitation
int slow_get_page_int(int key) { return key; }

struct Cache2QTestingData {
    size_t cache_size_;
    std::vector<int> input_;
    size_t hits_;
};

Cache2QTestingData refData[2] = {
        {
                .cache_size_=4,
                .input_={1, 2, 3, 4, 1, 2, 5, 1, 2, 4, 3, 4},
                .hits_=6
        },
        {
                .cache_size_=4,
                .input_={1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2},
                .hits_=0
        }
};
}

