#include <cassert>
#include <iostream>

#include "hw3d/Primitives3D.hpp"
#include "gtest/gtest.h"

namespace {

using namespace primitives3D;

TEST(PLANE, REL_POS_TEST)
{
    const Vec3 planeNormVec{0, 0, 1};
    const Vec3 planePoint{0, 0, 0};

    const Plane plane(planeNormVec, planePoint);

    Vec3 testPoint1{100, 100, 100};

    ASSERT_TRUE(plane.pointPosition(testPoint1) == PointRelPos::UPSIDE);

    Vec3 testPoint2{1.5, -1.3, 0.};

    ASSERT_TRUE(plane.pointPosition(testPoint2) == PointRelPos::DOWNSIDE);

    Vec3 testPoint3{-100., 0., -10.};

    ASSERT_TRUE(plane.pointPosition(testPoint3) == PointRelPos::DOWNSIDE);

}

}




