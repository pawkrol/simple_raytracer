#ifndef RIVAL_DEALER_SHADER_H
#define RIVAL_DEALER_SHADER_H


#include "math/Vector.h"
#include "Scene.h"

class Shader {

public:
    Vector shade(Vector hitPosition, Vector hitNormal, Scene scene, int primitiveIndex);

};


#endif //RIVAL_DEALER_SHADER_H
