#include "LRU.h"
#include "gtest/gtest.h"
#include "data/LRUTestingData.h"
#include "utils/utils.h"

namespace {

class LRUCacheTestingData : public ::testing::TestWithParam<testing_caches::CacheTestingData> {};

TEST_P(LRUCacheTestingData, HitsCount) {
    const auto params = GetParam();
    caches::cache_lru<int> c{params.cacheSize_};
    const size_t vec_size = params.input_.size();
    int hits = 0;
    for (int i = 0; i < vec_size; ++i) {
        if (c.lookup_update(params.input_[i], testing_caches::slow_get_page_int))
            hits += 1;
    }
    ASSERT_EQ(hits, params.hits_);
}

INSTANTIATE_TEST_SUITE_P(LRUCacheTesting, LRUCacheTestingData,
    ::testing::ValuesIn(cache_lru_testing::refData), tests_utils::PrintFileName());
}