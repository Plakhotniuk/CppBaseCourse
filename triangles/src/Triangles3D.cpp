#include "Triangles3D.hpp"

namespace triangles3D {

    void Triangle3D::setPoint(size_t ind, const Vec3& val){
        points_[ind] = val;
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

        return {planeNormVec, A + AH};
    }

    Plane Triangle3D::toPlane(const size_t point_ind) const 
    {
        return primitives3D::formTreePoints(points_[point_ind], points_[(point_ind + 1) % 3], points_[(point_ind + 2) % 3]);
    }

    bool Triangle3D::is_intersect(const Triangle3D& otherTriangle) const
    {
        // for point in thisTriangle.points
        for(size_t i = 0; i < 3; ++i) 
        {
            const Plane plane = constructPlane(i); // plane with normal directs to third point i
            const primitives3D::PointRelPos thisPointPos = plane.pointPosition(points_[i]);

            // for otherPoint in otherTriangle.points
            bool hasPointInHalfSpace = false;
            for(size_t j = 0; j < 3; ++j)
            {
                const auto otherPointPos = plane.pointPosition(otherTriangle.points_[j]);
                if(otherPointPos == thisPointPos || otherPointPos == primitives3D::PointRelPos::INPLANE)
                {
                    hasPointInHalfSpace = true;
                    break;
                }
            }
            if(!hasPointInHalfSpace) return false;
        }

        const Plane trianglePlane = toPlane(0);
        bool hasPointUpside = false;
        bool hasPointDownside = false;
        for(size_t i = 0; i < 3; ++i)
        {
            auto otherPointPos = trianglePlane.pointPosition(otherTriangle.points_[i]);
            if (otherPointPos == primitives3D::PointRelPos::INPLANE)
                return true;
            else if(otherPointPos == primitives3D::PointRelPos::UPSIDE) 
                hasPointUpside = true;
            else
                hasPointDownside = true;
        }
        return hasPointUpside && hasPointDownside;
    }

size_t countIntersections(const std::vector<Triangle3D>& triangles)
{
    size_t counter = 0;
    const size_t vecSize = triangles.size();
    for(size_t i = 0; i < vecSize - 1; ++i)
    {
        for(size_t j = i + 1; j < vecSize; ++j)
            if(triangles[i].is_intersect(triangles[j])) 
                ++counter;
    }
    return counter;
}    

}