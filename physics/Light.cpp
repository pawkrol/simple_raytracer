#include "Light.h"

Light::Light() = default;

Light::Light(Vector p, Vector color) : p(p), color(color) {}

Vector Light::getPosition() {
    return p;
}

Vector Light::getColor() {
    return color;
}

