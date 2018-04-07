#include "Scene.h"

Scene::Scene() = default;

void Scene::addPrimitive(Primitive *p) {
    primitives.push_back(p);
}

std::vector<Primitive *> Scene::getPrimitives() {
    return primitives;
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
