#include <cmath>
#include "Shader.h"

Vector Shader::shade(Vector hitPosition, Vector hitNormal, Scene scene, int sphereIndex) {
    Light light = scene.getLight();
    Sphere* sphere = scene.getSpheres()[sphereIndex];

    Vector toLight = light.getPosition() - hitPosition;
    toLight.normalize();
    Vector toCamera = scene.getCameraPosition() - hitPosition;
    toCamera.normalize();

    Vector halfway = toLight + toCamera;
    halfway.normalize();

    double ambientFactor = 0.04;
    double diffuseFactor = fmax(hitNormal.dot(toLight), 0);
    double specularFactor = pow(fmax(halfway.dot(hitNormal), 0), 32);

    Vector specularColor = light.getColor() * specularFactor;
    Vector diffuseColor = light.getColor() * diffuseFactor;
    Vector ambientColor = light.getColor() * ambientFactor;

    Ray shadowRay = Ray(hitPosition, toLight);
    double shadowFactor = 1;
    double t1, t2;
    for (int i = 0; i < scene.getSpheres().size(); i++) {
        if (i != sphereIndex && scene.getSpheres()[i]->intersects(shadowRay, t1, t2)) {
            if (t1 > 0) {
                shadowFactor = 0.2;
            }
        }
    }

    Vector finalColor = sphere->getColor() * ((diffuseColor * shadowFactor) + ambientColor);
    finalColor = finalColor + specularColor * shadowFactor;
    finalColor.min(1);

    return finalColor;
}
