#include <include/Triangles3D.hpp>
namespace triangles3D {

    std::array<Vec3, 2> Triangle3D::getTwoOtherPoints(size_t num) const 
    {
        return {points_[(num + 1) % 3], points_[(num + 2) % 3]};
    }

    Plane Triangle3D::constructPlane(size_t thirdPoint) const 
    {
        const Vec3 A = points_[(thirdPoint + 1) % 3];
        const Vec3 B = points_[(thirdPoint + 2) % 3];
        const Vec3 C = points_[thirdPoint];
        const Vec3 AB = B - A;
        const Vec3 AC = C - A;
        const Vec3 AH = AB.normalize() * AB.dot(AC) / AB.norm();
        const Vec3 planeNormVec = (AC - AH).normalize();

        return Plane(planeNormVec, A);
    }

    bool Triangle3D::is_intersect(const Triangle3D& otherTriangle) const
    {
        // for point in thisTriangle.points
        for(size_t i = 0; i < 3; ++i) 
        {
            const Plane plane = constructPlane(i);
            const primitives3D::PointRelPos thisPointPos = plane.pointPosition(points_[i]);

            // for otherPoint in otherTriangle.points
            bool hasPointInHalfSpace = false;
            for(size_t j = 0; j < 3; ++j)
            {
            const primitives3D::PointRelPos otherPointPos = plane.pointPosition(otherTriangle.points_[j]);
            if(otherPointPos == thisPointPos)
            {
                hasPointInHalfSpace = true;
                break;
            }
            }
            if(!hasPointInHalfSpace) return false;
        }
        return true;
    }

    size_t Triangle3D::countIntersections(const std::vector<Triangle3D>& triangles) const
    {
        size_t counter = 0;
        const size_t vecSize = triangles.size();
        for(size_t i = 0; i < vecSize - 1; ++i)
        {
            for(size_t j = i + 1; j < vecSize; ++j)
                if(is_intersect(triangles[j])) ++counter;
        }
        return counter;
    }

}