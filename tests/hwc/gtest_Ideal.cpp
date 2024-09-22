#include "src/CppBaseCourse/hwc/Ideal.h"
#include "gtest/gtest.h"

namespace {
// slow get page imitation
int slow_get_page_int(int key) { return key; }


TEST(TestIdeal, Test1) {
    int hits = 0;
    const size_t m = 4;
    caches::cache_ideal<int> c{m};

    const std::vector<int> input{1, 2, 3, 4, 1, 2, 5, 1, 2, 4, 3, 4};
    const size_t vec_size = input.size();
    for (int i = 0; i < vec_size; ++i) {
        if (c.lookup_update(input[i], slow_get_page_int, input, i))
            hits += 1;
    }
    ASSERT_EQ(hits, 6);
}

TEST(TestLRU, Test2) {
    int hits = 0;
    const size_t m = 4;
    caches::cache_ideal<int> c{m};

    const std::vector<int> input{1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2};
    const size_t vec_size = input.size();
    for (int i = 0; i < vec_size; ++i) {
        if (c.lookup_update(input[i], slow_get_page_int, input, i))
            hits += 1;
    }
    ASSERT_EQ(hits, 5);
}

}


