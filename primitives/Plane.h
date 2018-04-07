#ifndef RIVAL_DEALER_PLANE_H
#define RIVAL_DEALER_PLANE_H

#include "Primitive.h"

class Plane : public Primitive {

public:
    Plane() = default;
    Plane(Vector p, Vector n);
    Plane(Vector p, Vector n, Vector color);

    bool intersects(Ray r, double &t1, double &t2) override;
    Vector getNormal(Vector p) override;

    Vector getColor() override;

private:
    Vector p;
    Vector n;
    Vector color;

};


#endif //RIVAL_DEALER_PLANE_H
