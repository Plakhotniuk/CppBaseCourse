#pragma once

#include "CachesTestingCommon.h"

namespace cache_ideal_testing {
inline std::vector<testing_caches::CacheTestingData> refData = {
    {
        .testCaseName_ = "case1",
        .cacheSize_ = 5,
        .input_ = {6, 0, 9, 6, 3, 3, 7, 1, 4, 7, 1, 3, 3, 9, 6, 2, 1, 4, 1, 0},
        .hits_ = 10
    },
    {
        .testCaseName_ = "case2",
        .cacheSize_ = 4,
        .input_ = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2},
        .hits_ = 6
    },
    {
        .testCaseName_ = "case3",
        .cacheSize_ = 5,
        .input_ = {19, 3, 8, 6, 7, 5, 1, 0, 8, 4, 1, 4, 6, 8, 1, 6, 9, 5, 6, 7, 2, 2, 5, 2, 6, 1, 2, 5, 8, 1},
        .hits_ = 18
    }
};
}
