#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#include "math/Vector.h"
#include "physics/Ray.h"
#include "primitives/Sphere.h"
#include "physics/Light.h"
#include "Scene.h"
#include "Screen.h"
#include "Tracer.h"

int main() {
    unsigned width = 512;
    unsigned height = 512;
    double fov = 60;

    Screen screen(width, height, fov);

    Light light(Vector(0.12, 1, -0.5), Vector(1, 1, 1));

    Scene scene;
    scene.setCameraPosition(Vector(0, 0, 0));
    scene.addLight(light);
    scene.addSphere(new Sphere(Vector(-0.2, -0.2, -1), 0.2, Vector(0.9, 0, 0)));
    scene.addSphere(new Sphere(Vector(0.1, -0.1, -1.8), 0.45, Vector(1, 1, 1)));
    scene.addSphere(new Sphere(Vector(0.1, 0.2, -1), 0.2, Vector(0.55, 0.9, 0)));

    auto *image = Tracer().render(screen, scene, Shader());

    std::ofstream ofs("./image.ppm", std::ios::out | std::ios::binary);
    ofs << "P3\n" << width << " " << height << "\n255\n";
    for (unsigned i = 0; i < width * height; ++i) {
        ofs << floor(fmax(0, image[i].x) * 255) << " "
            << floor(fmax(0, image[i].y) * 255) << " "
            << floor(fmax(0, image[i].z) * 255) << " ";
    }
    ofs.close();

    delete[] image;

    return 0;
}