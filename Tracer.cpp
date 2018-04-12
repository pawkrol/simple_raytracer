#include <cmath>
#include <iostream>

#include "Tracer.h"
#include "physics/Ray.h"
#include "primitives/Sphere.h"
#include "math/Util.h"

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
    int primitiveIndex = -1;

    double tNearest = INFINITY;
    double t1 = 0;
    double t2 = 0;

    std::vector<Primitive*> primitives = scene.getPrimitives();

    for (int i = 0; i < primitives.size(); i++) {
        if (primitives[i]->intersects(ray, t1, t2)) {
            if (t1 < tNearest) {
                tNearest = t1;
                primitiveIndex = i;
            }
        }
    }

    if (primitiveIndex == -1) return Vector();

    Vector hitPosition = ray.getP() + ray.getD() * tNearest;
    Vector hitNormal = primitives[primitiveIndex]->getNormal(hitPosition);
    hitNormal.normalize();

    if (depth == 0) {
        Light light = scene.getLight();
        Vector toLight = Vector::normalize(light.getPosition() - hitPosition);
        Ray shadowRay = Ray(hitPosition, toLight);

        double distanceToLight = Vector::distance(hitPosition, light.getPosition());

        for (int i = 0; i < scene.getPrimitives().size(); i++) {
            Primitive* p = scene.getPrimitives()[i];
            if (i != primitiveIndex && !p->isTransparent() && p->intersects(shadowRay, t1, t2)) {
                Vector primitiveHitPosition = shadowRay.getP() + shadowRay.getD() * t1;
                double distanceToPrimitive = Vector::distance(hitPosition, primitiveHitPosition);

                if (distanceToPrimitive < distanceToLight) {
                    return shader.shade(hitPosition, hitNormal, scene, primitiveIndex) * 0.2;
                }
            }
        }
    }

    Vector calculatedColor;

    if (depth < MAX_DEPTH) {
        double kt = 0;
        double kr = 0;

        double rayDirDotNormal = ray.getD().dot(hitNormal);
        double cosi = Util::clamp(-1.0, 1.0, rayDirDotNormal);
        double etai = 1;
        double etat = 1.47;

        Vector n = hitNormal;

        if (cosi < 0) {
            cosi = -cosi;
        } else {
            double e = etat;
            etat = etai;
            etai = e;

            n = -hitNormal;
        }

        double eta = etai / etat;
        double u = 1.0 - cosi * cosi;
        double k = 1.0 - eta * eta * u;

        double sint = eta * sqrt(Util::max(0.0, u));

        if (sint >= 1) {
            kr = 1;
        } else {
            double cost = sqrt(Util::max(0.0, 1 - sint * sint));
            double cosiAbs = Util::abs(cosi);
            double Rs = ( (etat * cosiAbs) - (etai * cost) ) / ( (etat * cosiAbs) + (etai * cost) );
            double Rp = ( (etai * cosiAbs) - (etat * cost) ) / ( (etai * cosiAbs) + (etat * cost) );
            kr = (Rs * Rs + Rp * Rp) / 2;
        }

        kt = 1 - kr;

        //refraction
        if (primitives[primitiveIndex]->isTransparent()) {
            bool outside = rayDirDotNormal < 0;

            Vector refractedOrigin = outside ? hitPosition - hitNormal * BIAS : hitPosition + hitNormal * BIAS;
            Vector refractedDir = k < 0 ? Vector(0) : ray.getD() * eta + n * (eta * cosi - sqrt(k));
            refractedDir.normalize();

            Ray refractedRay(refractedOrigin, refractedDir);
            calculatedColor += trace(scene, refractedRay, shader, depth + 1) * kt;
        }

        //reflection
        Vector reflectedDir = Vector::normalize(Vector::reflect(ray.getD(), hitNormal));

        Ray reflectRay(hitPosition + (hitNormal * BIAS), reflectedDir);
        calculatedColor += trace(scene, reflectRay, shader, depth + 1) * kr;
    }

    return calculatedColor + shader.shade(hitPosition, hitNormal, scene, primitiveIndex);
}
