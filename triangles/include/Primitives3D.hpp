#pragma once
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>


namespace primitives3D {

class Vec3 {
    double x_, y_, z_;

public:
    constexpr static double tolerance = std::numeric_limits<double>::epsilon();
    // Constructors
    Vec3() : x_(0), y_(0), z_(0) {}               
    Vec3(double x, double y, double z) : x_(x), y_(y), z_(z) {} 

    // Basic vector operations
    Vec3 operator+(const Vec3& other) const {  
        return {x_ + other.x_, y_ + other.y_, z_ + other.z_};
    }

    Vec3 operator-(const Vec3& other) const {  
        return {x_ - other.x_, y_ - other.y_, z_ - other.z_};
    }

    Vec3 operator*(const double scalar) const {       
        return {x_ * scalar, y_ * scalar, z_ * scalar};
    }

    Vec3 operator/(const double scalar) const {       
        return {x_ / scalar, y_ / scalar, z_ / scalar};
    }

    double dot(const Vec3& other) const {
        return x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
    }

    Vec3 cross(const Vec3& other) const 
    {
        return {
            y_ * other.z_ - z_ * other.y_,
            z_ * other.x_ - x_ * other.z_,
            x_ * other.y_ - y_ * other.x_,
        };
    }

    double norm() const {
        return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_);
    }

    Vec3 normalize() const {
        double mag = norm();
        return {x_ / mag, y_ / mag, z_ / mag};
    }

    bool isEqual(const Vec3& other)
    {
        return std::abs(x_ - other.x_) < tolerance && std::abs(y_ - other.y_) < tolerance && std::abs(z_ - other.z_) < tolerance;
    }

    void display() const {
        std::cout << "(" << x_ << ", " << y_ << ", " << z_ << ")\n";
    }

    friend std::istream& operator>>(std::istream& in, Vec3& vec){
        in >> vec.x_ >> vec.y_ >> vec.z_;
        return in;
    }

};

enum class PointRelPos {
    UPSIDE,
    DOWNSIDE,
    INPLANE
};

class Plane {

    Vec3 normVec_;
    Vec3 planePoint_;
    
public:

    Plane(const Vec3& normVec, const Vec3& point): normVec_(normVec), planePoint_(point) {};

    [[nodiscard]] PointRelPos pointPosition(const Vec3& point) const {
        const auto res = (point - planePoint_).dot(normVec_);

        if(res > Vec3::tolerance) 
            return PointRelPos::UPSIDE;

        if(std::abs(res) <= Vec3::tolerance) 
            return PointRelPos::INPLANE;

        return PointRelPos::DOWNSIDE;
    }
};

Plane static inline formTreePoints(const Vec3& A, const Vec3& B, const Vec3& C)
{
    const Vec3 AB = B - A;
    const Vec3 AC = C - A;
    const Vec3 n = (AC.cross(AB)).normalize();

    return {n, A};
}

}
