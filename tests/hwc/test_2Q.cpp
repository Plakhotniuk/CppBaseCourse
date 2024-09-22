#include "src/CppBaseCourse/hwc/2Q.h"
#include "gtest/gtest.h"

namespace {
// slow get page imitation
int slow_get_page_int(int key) { return key; }


TEST(Test2Q, Test1) {
    int hits = 0;
    const size_t m1 = 2;
    const size_t m2 = 4;
    caches::cache_2q<int> c(m1, m2);

    const std::vector<int> input{1, 2, 3, 4, 1, 2, 5, 1, 2, 4, 3, 4};
    const size_t vec_size = input.size();
    for (size_t i = 0; i < vec_size; ++i) {
        if (c.lookup_update(input[i], slow_get_page_int))
            hits += 1;
    }
    ASSERT_EQ(hits, 7);
}
}


