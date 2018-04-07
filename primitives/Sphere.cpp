#include <cmath>
#include "Sphere.h"

Sphere::Sphere(Vector c, double r): c(c), r(r) {
    color = Vector(0, 0, 0);
}

Sphere::Sphere(Vector c, double r, Vector color): c(c), r(r), color(color){}

bool Sphere::intersects(Ray ray, double &t1, double &t2) {
    // analytic solution
//    Vector L = ray.getP() - c;
//
//    double a = ray.getD().dot(ray.getD()); // d * d
//    double b = 2 * ray.getD().dot(L); // 2 * d * (p - c)
//    double c = L.dot(L) - (r * r); // (p - c) * (p - c) - r^2
//
//    double delta = b * b - 4 * a * c;
//
//    if (delta < 0) {
//        t1 = INFINITY;
//        t2 = INFINITY;
//
//        return false;
//    }
//
//    if (delta > 0) {
//        double aTimes2 = a * 2;
//        double sqrtDelta = sqrt(delta);
//
//        t1 = (-b - sqrtDelta) / aTimes2;
//        t2 = (-b + sqrtDelta) / aTimes2;
//    }
//
//    if (delta == 0) {
//        t1 = -b / (2 * a);
//        t2 = t1;
//    }

    //geometric solution
    Vector l = c - ray.getP();

    double tca = l.dot(ray.getD());
    if (tca < 0) return false;

    double d2 = l.dot(l) - tca * tca;
    double radius2 = r * r;
    if (d2 > radius2) return false;

    double thc = sqrt(radius2 - d2);
    t1 = tca - thc;
    t2 = tca + thc;

    if (t1 > t2) {
        double t = t2;
        t2 = t1;
        t1 = t;
    }

    if (t1 < 0) {
        t1 = t2;
        if (t1 < 0) return false;
    }

    return true;
}

Vector Sphere::getNormal(Vector p) {
    return p - c;
}

Vector Sphere::getCenter() {
    return c;
}

Vector Sphere::getColor() {
    return color;
}
