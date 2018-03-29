#include <cmath>

#include "Tracer.h"
#include "physics/Ray.h"
#include "primitives/Sphere.h"

const double PI = 3.1415926;

Vector *Tracer::render(Screen screen, Scene scene, Shader shader) {
    auto *image = new Vector[screen.width * screen.height];
    for (unsigned i = 0; i < screen.width * screen.height; ++i) {
        image[i] = Vector(0, 0, 0);
    }

    double aspectRatio = screen.getAspectRatio();
    double tanAlpha = tan( (PI / 180.) * 0.5 * screen.fov );
    double inverseWidth = 1 / double(screen.width);
    double inverseHeight = 1 / double(screen.height);

    double px, py;

    for (int y = 0; y < screen.height; y++) {
        py = (1 - (2 * (y + 0.5) * inverseHeight)) * tanAlpha;

        for (int x = 0; x < screen.width; x++) {
            px = (2 * (x + 0.5) * inverseWidth - 1) * aspectRatio * tanAlpha;

            Vector d(px, py, -1); //forward: negative Z axis
            d.normalize();
            Ray ray(scene.getCameraPosition(), d);

            image[y * screen.width + x] = trace(scene, ray, shader);
        }
    }

    return image;
}

Vector Tracer::trace(Scene scene, Ray ray, Shader shader) {
    int sphereIndex = -1;

    double tNearest = INFINITY;
    double t1 = 0;
    double t2 = 0;

    std::vector<Sphere*> spheres = scene.getSpheres();

    for (int i = 0; i < spheres.size(); i++) {
        if (spheres[i]->intersects(ray, t1, t2)) {
            if (t1 < 0) t1 = t2;
            if (t1 < tNearest) {
                tNearest = t1;
                sphereIndex = i;
            }
        }
    }

    if (sphereIndex == -1) return Vector(0, 0, 0);

    Vector hitPosition = ray.getP() + ray.getD() * tNearest;
    Vector hitNormal = hitPosition - spheres[sphereIndex]->getCenter(); //for now just support Sphere
    hitNormal.normalize();

    return shader.shade(hitPosition, hitNormal, scene, sphereIndex);
}
