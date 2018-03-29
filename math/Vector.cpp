#include <cmath>

#include "Vector.h"

Vector::Vector(): x(0), y(0), z(0) {}

Vector::Vector(double x, double y): x(x), y(y), z(0) {}

Vector::Vector(double x, double y, double z): x(x), y(y), z(z) {}

std::string Vector::print() {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
}

void Vector::normalize() {
    double m = sqrt((x * x) + (y * y) + (z * z));

    x /= m;
    y /= m;
    z /= m;
}

void Vector::max(double max) {
    x = fmax(x, max);
    y = fmax(y, max);
    z = fmax(z, max);
}

void Vector::min(double min) {
    x = fmin(x, min);
    y = fmin(y, min);
    z = fmin(z, min);
}

double Vector::dot(Vector v) {
    return x * v.x + y * v.y + z * v.z;
}

Vector Vector::cross(Vector v) {
    double tx = y * v.z - z * v.y;
    double ty = z * v.x - x * v.z;
    double tz = x * v.y - y * v.x;

    return Vector(tx, ty, tz);
}

Vector Vector::operator-(Vector v) {
    Vector tmp(*this);
    tmp.x -= v.x;
    tmp.y -= v.y;
    tmp.z -= v.z;
    return tmp;
}

Vector Vector::operator+(Vector v) {
    Vector tmp(*this);
    tmp.x += v.x;
    tmp.y += v.y;
    tmp.z += v.z;
    return tmp;
}

Vector Vector::operator*(double v) {
    Vector tmp(*this);
    tmp.x *= v;
    tmp.y *= v;
    tmp.z *= v;
    return tmp;
}

Vector Vector::operator*(Vector v) {
    Vector tmp(*this);
    tmp.x *= v.x;
    tmp.y *= v.y;
    tmp.z *= v.z;
    return tmp;
}