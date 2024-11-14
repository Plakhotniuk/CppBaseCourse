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
    // Constructors
    Vec3() : x_(0), y_(0), z_(0) {}               // Default constructor
    Vec3(double x, double y, double z) : x_(x), y_(y), z_(z) {} // Parameterized constructor

    // Basic vector operations
    Vec3 operator+(const Vec3& other) const {  // Vector addition
        return {x_ + other.x_, y_ + other.y_, z_ + other.z_};
    }

    Vec3 operator-(const Vec3& other) const {  // Vector subtraction
        return {x_ - other.x_, y_ - other.y_, z_ - other.z_};
    }

    Vec3 operator*(const double scalar) const {       
        return {x_ * scalar, y_ * scalar, z_ * scalar};
    }

    Vec3 operator/(const double scalar) const {       
        return {x_ / scalar, y_ / scalar, z_ / scalar};
    }

    // Dot product
    double dot(const Vec3& other) const {
        return x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
    }

    double norm() const {
        return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_);
    }

    Vec3 normalize() const {
        double mag = norm();
        return {x_ / mag, y_ / mag, z_ / mag};
    }

    // Utility function to display the vector
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
};

class Plane {

    Vec3 normVec_;
    Vec3 planePoint_;
    
public:

    Plane(const Vec3& normVec, const Vec3& point): normVec_(normVec), planePoint_(point) {};

    [[nodiscard]] PointRelPos pointPosition(const Vec3& point) const {
        const auto res = (point - planePoint_).dot(normVec_);
        return res >= 0 ? PointRelPos::UPSIDE : PointRelPos::DOWNSIDE;
    }
};

}
