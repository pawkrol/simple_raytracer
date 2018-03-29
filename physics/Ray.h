#ifndef RIVAL_DEALER_RAY_H
#define RIVAL_DEALER_RAY_H

#include "../math/Vector.h"

class Ray {

public:
    Ray() = default;
    Ray(Vector p, Vector d);

    Vector getP();
    Vector getD();

private:
    Vector p;
    Vector d;

};

#endif //RIVAL_DEALER_RAY_H
