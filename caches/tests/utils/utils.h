#pragma once
#include <gtest/gtest.h>

namespace tests_utils {
struct PrintFileName
{
    template<class ParamType>
    std::string operator()(const ::testing::TestParamInfo<ParamType>& info) const
    {
        return std::string(info.param.testCaseName_);
    }
};
}
