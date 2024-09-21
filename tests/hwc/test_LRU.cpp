#include "src/CppBaseCourse/hwc/LRU.h"
#include "gtest/gtest.h"
#include <array>

// slow get page imitation
int slow_get_page_int(int key) { return key; }


TEST(TestLRU, Test1) {
    int hits = 0;
    int n = 10;
    size_t m = 4;
    caches::cache_lru<int> c{m};

    std::array<int, 10> input{1, 3, 5, 3, 2, 4, 3, 5, 4, 5};

    for (int i = 0; i < n; ++i) {
        if (c.lookup_update(input[i], slow_get_page_int))
            hits += 1;
    }
    ASSERT_TRUE(hits == 5);
}