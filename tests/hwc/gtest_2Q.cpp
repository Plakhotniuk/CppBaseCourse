#include "src/CppBaseCourse/hwc/2Q.h"
#include "tests/data/hwc/2QTestingData.h"
#include "gtest/gtest.h"
#include "tests/utils/utils.h"

namespace {

TEST(Cache2QTest, EndToEnd){
    caches::cache_2q<int> c{2};
    const std::vector<int> input = {1, 1, 2, 3, 1, 2};
    bool hit;
    hit = c.lookup_update(input[0], testing_caches::slow_get_page_int);
    ASSERT_TRUE(!hit);

    hit = c.lookup_update(input[1], testing_caches::slow_get_page_int);
    ASSERT_TRUE(hit);

    hit = c.lookup_update(input[2], testing_caches::slow_get_page_int);
    ASSERT_TRUE(!hit);

    hit = c.lookup_update(input[3], testing_caches::slow_get_page_int);
    ASSERT_TRUE(!hit);

    hit = c.lookup_update(input[4], testing_caches::slow_get_page_int);
    ASSERT_TRUE(hit);

    hit = c.lookup_update(input[5], testing_caches::slow_get_page_int);
    ASSERT_TRUE(hit);
}

class Cache2QTestingData : public ::testing::TestWithParam<testing_caches::CacheTestingData> {};

TEST_P(Cache2QTestingData, HitsCount)
{
    const auto params = GetParam();
    caches::cache_2q<int> c{params.cacheSize_};
    const size_t vec_size = params.input_.size();
    int hits = 0;
    for (int i = 0; i < vec_size; ++i)
    {
        if (c.lookup_update(params.input_[i], testing_caches::slow_get_page_int))
            hits += 1;
    }
    ASSERT_EQ(hits, params.hits_);
}

INSTANTIATE_TEST_SUITE_P(Cache2QTesting, Cache2QTestingData,
                         ::testing::ValuesIn(cache_2q_testing::refData), tests_utils::PrintFileName());
}
