#include <cassert>
#include <iostream>
#include "hw3d/Triangles3D.hpp"
#include "gtest/gtest.h"

namespace {

using namespace triangles3D;

TEST(TRINAGLES_INTERSECTION, TEST1)
{
    // write from file, check with result
    Triangle3D tr1{{1, 1, 2}, {1, 1, 2}, {2, 2, 2}};
    Triangle3D tr2{{1, 1, 1}, {1, 5, 1}, {5, 1, 1}};

    bool result = tr1.is_intersect(tr2);

    ASSERT_FALSE(result);
}

}