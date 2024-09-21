#include "src/CppBaseCourse/hwc/2Q.h"
#include "gtest/gtest.h"
#include <array>

namespace {
// slow get page imitation
int slow_get_page_int(int key) { return key; }

TEST(Test2Q, Test1) {
    int hits = 0;
    size_t m1 = 2;
    size_t m2 = 2;
    caches::cache_2q<int> c(m1, m2);

    std::vector<int> input{1, 3, 5, 3, 2, 4, 3, 5, 4, 5};
    int vec_size = input.size();
    for (int i = 0; i < vec_size; ++i) {
        if (c.lookup_update(input[i], slow_get_page_int))
            hits += 1;
    }
    ASSERT_EQ(hits, 5);
}
}


