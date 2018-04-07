#include <cmath>
#include "Shader.h"

Vector Shader::shade(Vector hitPosition, Vector hitNormal, Scene scene, int primitiveIndex) {
    Light light = scene.getLight();
    Primitive* primitive = scene.getPrimitives()[primitiveIndex];

    Vector toLight = Vector::normalize(light.getPosition() - hitPosition);
    Vector toCamera = Vector::normalize(scene.getCameraPosition() - hitPosition);
    Vector halfway = Vector::normalize(toLight + toCamera);

    double ambientFactor = 0.08;
    double diffuseFactor = fmax(hitNormal.dot(toLight), 0);
    double specularFactor = pow(fmax(halfway.dot(hitNormal), 0), 64);

    Vector specularColor = light.getColor() * specularFactor;
    Vector diffuseColor = light.getColor() * diffuseFactor;
    Vector ambientColor = light.getColor() * ambientFactor;

    return primitive->getColor() * (diffuseColor + ambientColor) + specularColor;
}
