#include "src/CppBaseCourse/hwc/Ideal.h"
#include "tests/data/hwc/IdealTestingData.h"
#include "gtest/gtest.h"
#include "tests/utils/utils.h"

namespace {

TEST(IdealCacheTest, EndToEnd){
    caches::cache_ideal<int> c{2};
    const std::vector<int> input = {1, 2, 3, 1};
    bool hit;
    hit = c.lookup_update(input[0], testing_caches::slow_get_page_int, input, 0);
    ASSERT_TRUE(!hit);

    ASSERT_TRUE(!c.full());

    hit = c.lookup_update(input[1], testing_caches::slow_get_page_int, input, 1);
    ASSERT_TRUE(!hit);

    ASSERT_TRUE(c.full());

    hit = c.lookup_update(input[2], testing_caches::slow_get_page_int, input, 2);
    ASSERT_TRUE(!hit);

    hit = c.lookup_update(input[3], testing_caches::slow_get_page_int, input, 3);
    ASSERT_TRUE(hit);
}

class CacheIdealTestingData : public ::testing::TestWithParam<testing_caches::CacheTestingData> {};

TEST_P(CacheIdealTestingData, HitsCount)
{
    const auto params = GetParam();
    caches::cache_ideal<int> c{params.cacheSize_};
    const size_t vec_size = params.input_.size();
    int hits = 0;
    for (int i = 0; i < vec_size; ++i)
    {
        if (c.lookup_update(params.input_[i], testing_caches::slow_get_page_int, params.input_, i))
            hits += 1;
    }
    ASSERT_EQ(hits, params.hits_);
}

INSTANTIATE_TEST_SUITE_P(IdealCacheTesting, CacheIdealTestingData,
                         ::testing::ValuesIn(cache_ideal_testing::refData), tests_utils::PrintFileName());
}
