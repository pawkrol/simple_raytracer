#include <cmath>
#include "Sphere.h"

Sphere::Sphere(Vector c, double r): c(c), r(r) {
    color = Vector(0, 0, 0);
}

Sphere::Sphere(Vector c, double r, Vector color): c(c), r(r), color(color){}

bool Sphere::intersects(Ray ray, double &t1, double &t2) {
    Vector pMinusC = ray.getP() - c;

    double a = ray.getD().dot(ray.getD()); // d * d
    double b = 2 * ray.getD().dot(pMinusC); // 2 * d * (p - c)
    double c = pMinusC.dot(pMinusC) - (r * r); // (p - c) * (p - c) - r^2

    double delta = b * b - 4 * a * c;

    if (delta > 0) {
        double aTimes2 = a * 2;
        double sqrtDelta = sqrt(delta);

        t1 = (-b - sqrtDelta) / aTimes2;
        t2 = (-b + sqrtDelta) / aTimes2;

        return true;
    }

    if (delta == 0) {
        t1 = -INFINITY;
        t2 = -b / (2 * a);

        return true;
    }

    t1 = -INFINITY;
    t2 = -INFINITY;

    return false;
}

Vector Sphere::getCenter() {
    return c;
}

Vector Sphere::getColor() {
    return color;
}
