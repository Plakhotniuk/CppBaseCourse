#include "src/CppBaseCourse/hwc/LRU.h"
#include "gtest/gtest.h"

namespace {
// slow get page imitation
int slow_get_page_int(int key) { return key; }


TEST(TestLRU, Test1) {
    int hits = 0;
    const size_t m = 4;
    caches::cache_lru<int> c{m};

    const std::vector<int> input{1, 2, 3, 4, 1, 2, 5, 1, 2, 4, 3, 4};
    const size_t vec_size = input.size();
    for (size_t i = 0; i < vec_size; ++i) {
        if (c.lookup_update(input[i], slow_get_page_int))
            hits += 1;
    }
    ASSERT_EQ(hits, 6);
}
}