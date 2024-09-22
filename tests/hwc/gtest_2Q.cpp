#include "src/CppBaseCourse/hwc/2Q.h"
#include "tests/data/hwc/2QTestingData.h"
#include "gtest/gtest.h"

namespace {

class Cache2QTestingData : public ::testing::TestWithParam<cache_2q_testing::Cache2QTestingData> {};

TEST_P(Cache2QTestingData, HitsCount) {
    const auto params = GetParam();
    caches::cache_lru<int> c{params.cache_size_};
    const size_t vec_size = params.input_.size();
    int hits = 0;
    for (int i = 0; i < vec_size; ++i) {
        if (c.lookup_update(params.input_[i], cache_2q_testing::slow_get_page_int))
            hits += 1;
    }
    ASSERT_EQ(hits, params.hits_);
}

INSTANTIATE_TEST_SUITE_P(LRUCacheTestingdata, Cache2QTestingData, ::testing::ValuesIn(cache_2q_testing::refData));
}



