#pragma once

#include <vector>
#include "CachesTestingCommon.h"

namespace cache_ideal_testing {
inline std::vector<testing_caches::CacheTestingData> refData = {
    {
        .testCaseName_ = "case1",
        .cacheSize_ = 2,
        .input_ = {1, 2, 3, 1},
        .hits_ = 1
    },
    {
        .testCaseName_ = "case2",
        .cacheSize_ = 4,
        .input_ = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2},
        .hits_ = 6
    },
    {
        .testCaseName_ = "case3",
        .cacheSize_ = 4,
        .input_ = {1, 1, 2, 1, 3, 1, 4, 3, 5, 7, 1},
        .hits_ = 5
    }
};
}