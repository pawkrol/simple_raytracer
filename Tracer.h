#ifndef RIVAL_DEALER_TRACER_H
#define RIVAL_DEALER_TRACER_H

#include "math/Vector.h"
#include "Screen.h"
#include "Scene.h"
#include "Shader.h"

class Tracer {

public:
    Vector* render(Screen screen, Scene scene, Shader shader);

private:
    Vector trace(Scene scene, Ray ray, Shader shader, int depth);

};


#endif //RIVAL_DEALER_TRACER_H
