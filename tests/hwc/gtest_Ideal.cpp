#include "src/CppBaseCourse/hwc/Ideal.h"
#include "tests/data/hwc/IdealTestingData.h"
#include "gtest/gtest.h"
#include "tests/utils/utils.h"

namespace {

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
