#include "Ray.h"

Ray::Ray(const Vector p, const Vector d): p(p), d(d) {}

Vector Ray::getP() {
    return p;
}

Vector Ray::getD() {
    return d;
}
