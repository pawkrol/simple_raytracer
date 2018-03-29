#ifndef RIVAL_DEALER_SPHERE_H
#define RIVAL_DEALER_SPHERE_H

#include "../math/Vector.h"
#include "../physics/Ray.h"

class Sphere {

public:
    Sphere() = default;
    Sphere(Vector c, double r);
    Sphere(Vector c, double r, Vector color);

    bool intersects(Ray r, double &t1, double &t2);

    Vector getCenter();
    Vector getColor();

private:
    Vector c;
    double r = 0;

    Vector color;

};


#endif //RIVAL_DEALER_SPHERE_H
