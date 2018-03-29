#ifndef RIVAL_DEALER_LIGHT_H
#define RIVAL_DEALER_LIGHT_H


#include "../math/Vector.h"

class Light {

public:
    Light(Vector p, Vector color);

    Light();

    Vector getPosition();
    Vector getColor();

private:
    Vector p;
    Vector color;

};


#endif //RIVAL_DEALER_LIGHT_H
