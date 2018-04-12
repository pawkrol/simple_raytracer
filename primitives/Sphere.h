#ifndef RIVAL_DEALER_SPHERE_H
#define RIVAL_DEALER_SPHERE_H

#include "Primitive.h"

class Sphere : public Primitive{

public:
    Sphere() = default;
    Sphere(Vector c, double r);
    Sphere(Vector c, double r, Vector color);

    bool intersects(Ray r, double &t1, double &t2) override;
    Vector getNormal(Vector p) override;

    Vector getCenter();
    Vector getColor() override;
    bool isTransparent() override;

private:
    Vector c;
    double r = 0;

    Vector color;

};


#endif //RIVAL_DEALER_SPHERE_H
