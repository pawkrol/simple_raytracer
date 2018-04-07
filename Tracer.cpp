#include <cmath>
#include <iostream>

#include "Tracer.h"
#include "physics/Ray.h"
#include "primitives/Sphere.h"

const double PI = 3.1415926;
const double BIAS = 1e-12;
const int MAX_DEPTH = 8;

Vector *Tracer::render(Screen screen, Scene scene, Shader shader) {
    auto *image = new Vector[screen.width * screen.height];

    double aspectRatio = screen.getAspectRatio();
    double tanAlpha = tan( (PI / 180.) * 0.5 * screen.fov );
    double inverseWidth = 1.0 / double(screen.width);
    double inverseHeight = 1.0 / double(screen.height);

    double px, py;

    for (int y = 0; y < screen.height; y++) {
        py = (1 - (2 * (y + 0.5) * inverseHeight)) * tanAlpha;

        for (int x = 0; x < screen.width; x++) {
            px = (2 * (x + 0.5) * inverseWidth - 1) * aspectRatio * tanAlpha;

            Vector d(px, py, -1); //forward: negative Z axis
            d.normalize();
            Ray ray(scene.getCameraPosition(), d);

            image[y * screen.width + x] = trace(scene, ray, shader, 0);
            image[y * screen.width + x].min(1);
        }
    }

    return image;
}

Vector Tracer::trace(Scene scene, Ray ray, Shader shader, int depth) {
    int sphereIndex = -1;

    double tNearest = INFINITY;
    double t1 = 0;
    double t2 = 0;

    std::vector<Primitive*> primitives = scene.getPrimitives();

    for (int i = 0; i < primitives.size(); i++) {
        if (primitives[i]->intersects(ray, t1, t2)) {
            if (t1 < tNearest) {
                tNearest = t1;
                sphereIndex = i;
            }
        }
    }

    if (sphereIndex == -1) return Vector(0, 0, 0);

    Vector hitPosition = ray.getP() + ray.getD() * tNearest;
    Vector hitNormal = primitives[sphereIndex]->getNormal(hitPosition);
    hitNormal.normalize();

    Vector toLight = Vector::normalize(scene.getLight().getPosition() - hitPosition);
    Ray shadowRay = Ray(hitPosition, toLight);

    for (int i = 0; i < scene.getPrimitives().size(); i++) {
        if (i != sphereIndex && scene.getPrimitives()[i]->intersects(shadowRay, t1, t2)) {
            return shader.shade(hitPosition, hitNormal, scene, sphereIndex) * 0.2;
        }
    }

    Vector calculatedColor;

    if (depth < MAX_DEPTH) {
        Vector reflectedDir = Vector::normalize(Vector::reflect(ray.getD(), hitNormal));

        Ray reflectRay(hitPosition + (hitNormal * BIAS), reflectedDir);
        calculatedColor = trace(scene, reflectRay, shader, depth + 1) * 0.3;
    }

    return calculatedColor + shader.shade(hitPosition, hitNormal, scene, sphereIndex);
}
