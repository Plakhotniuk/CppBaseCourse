#include "Ideal.h"
#include "data/IdealTestingData.h"
#include "gtest/gtest.h"
#include "utils/utils.h"
#include <span>

namespace {

class CacheIdealTestingData : public ::testing::TestWithParam<testing_caches::CacheTestingData> {};

TEST_P(CacheIdealTestingData, HitsCount)
{
    const auto params = GetParam();
    caches::cache_ideal c(params.cacheSize_);
    int hits = c.lookup_update(params.input_);

    ASSERT_EQ(hits, params.hits_);
}

INSTANTIATE_TEST_SUITE_P(IdealCacheTesting, CacheIdealTestingData,
                         ::testing::ValuesIn(cache_ideal_testing::refData), tests_utils::PrintFileName());
}
