#ifndef RIVAL_DEALER_SCENE_H
#define RIVAL_DEALER_SCENE_H

#include <vector>
#include "primitives/Sphere.h"
#include "physics/Light.h"

class Scene {

public:
    Scene();

    void addSphere(Sphere *p);
    std::vector<Sphere*> getSpheres();

    void addLight(Light l);
    Light getLight();

    void setCameraPosition(Vector cp);
    Vector getCameraPosition();

private:
    std::vector<Sphere*> spheres;
    Light light; // for now only one
    Vector cameraPosition;

};


#endif //RIVAL_DEALER_SCENE_H
