#include "src/CppBaseCourse/hwc/Ideal.h"
#include "tests/data/hwc/IdealTestingData.h"
#include "gtest/gtest.h"
#include "tests/utils/utils.h"
#include <span>

namespace {

// class CacheIdealTestingData : public ::testing::TestWithParam<testing_caches::CacheTestingData> {};

// TEST_P(CacheIdealTestingData, HitsCount)
// {
//     const auto params = GetParam();
//     caches::cache_ideal c(params.cacheSize_, params.input_);
//     const size_t vec_size = params.input_.size();
//     int hits = c.lookup_update();

//     ASSERT_EQ(hits, params.hits_);
// }

// INSTANTIATE_TEST_SUITE_P(IdealCacheTesting, CacheIdealTestingData,
//                          ::testing::ValuesIn(cache_ideal_testing::refData), tests_utils::PrintFileName());
}
