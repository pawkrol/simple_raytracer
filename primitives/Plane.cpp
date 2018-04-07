#include <cmath>
#include "Plane.h"

Plane::Plane(Vector p, Vector n): p(p) {
    this->n = Vector::normalize(n);
}

Plane::Plane(Vector p, Vector n, Vector color): p(p), color(color) {
    this->n = Vector::normalize(n);
}

bool Plane::intersects(Ray r, double &t1, double &t2) {
    double denom = n.dot(r.getD());
    if (denom < 1e-12) {
        double t = n.dot(p - r.getP()) / denom;
        t1 = t;
        t2 = t;

        return (t >= 0);
    }

    return false;
}

Vector Plane::getNormal(Vector p) {
    return n;
}

Vector Plane::getColor() {
    return color;
}



