#pragma once
#include <string_view>
#include <vector>
namespace testing_caches {
// slow get page imitation
int slow_get_page_int(int key) { return key; }

struct CacheTestingData
{
    std::string_view testCaseName_;
    size_t cacheSize_;
    std::vector<int> input_;
    size_t hits_;
};
}
