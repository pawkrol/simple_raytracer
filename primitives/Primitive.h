#ifndef RIVAL_DEALER_PRIMITIVE_H
#define RIVAL_DEALER_PRIMITIVE_H

#include "../physics/Ray.h"

class Primitive {

public:
    virtual bool intersects(Ray r, double &t1, double &t2) = 0;
    virtual Vector getNormal(Vector position) = 0;
    virtual Vector getColor() = 0;
    virtual bool isTransparent() {
        return false;
    }

};

#endif //RIVAL_DEALER_PRIMITIVE_H
