#ifndef RIVAL_DEALER_SCENE_H
#define RIVAL_DEALER_SCENE_H

#include <vector>
#include "primitives/Primitive.h"
#include "physics/Light.h"

class Scene {

public:
    Scene();

    void addPrimitive(Primitive *p);
    std::vector<Primitive *> getPrimitives();

    void addLight(Light l);
    Light getLight();

    void setCameraPosition(Vector cp);
    Vector getCameraPosition();

private:
    std::vector<Primitive*> primitives;
    Light light; // for now only one
    Vector cameraPosition;

};


#endif //RIVAL_DEALER_SCENE_H
