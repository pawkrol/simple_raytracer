#include "Scene.h"

Scene::Scene() = default;

void Scene::addSphere(Sphere *p) {
    spheres.push_back(p);
}

std::vector<Sphere*> Scene::getSpheres() {
    return spheres;
}

void Scene::addLight(Light l) {
    light = l;
}

Light Scene::getLight() {
    return light;
}

void Scene::setCameraPosition(Vector cp) {
    cameraPosition = cp;
}

Vector Scene::getCameraPosition() {
    return cameraPosition;
}
