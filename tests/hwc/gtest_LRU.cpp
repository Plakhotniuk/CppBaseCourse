#include "src/CppBaseCourse/hwc/LRU.h"
#include "gtest/gtest.h"
#include "tests/data/hwc/LRUTestingData.h"

namespace {

class LRUCacheTestingData : public ::testing::TestWithParam<cache_lru_testing::CacheLRUTestingData> {};

TEST_P(LRUCacheTestingData, HitsCount) {
    const auto params = GetParam();
    caches::cache_lru<int> c{params.cache_size_};
    const size_t vec_size = params.input_.size();
    int hits = 0;
    for (int i = 0; i < vec_size; ++i) {
        if (c.lookup_update(params.input_[i], cache_lru_testing::slow_get_page_int))
            hits += 1;
    }
    ASSERT_EQ(hits, params.hits_);
}

INSTANTIATE_TEST_SUITE_P(LRUCacheTestingdata, LRUCacheTestingData, ::testing::ValuesIn(cache_lru_testing::refData));
}