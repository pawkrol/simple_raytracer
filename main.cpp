#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <chrono>

#include "math/Vector.h"
#include "physics/Ray.h"
#include "primitives/Sphere.h"
#include "physics/Light.h"
#include "Scene.h"
#include "Screen.h"
#include "Tracer.h"
#include "primitives/Plane.h"

int main() {
    unsigned width = 640;
    unsigned height = 480;
    double fov = 80;

    Screen screen(width, height, fov);

    Light light(Vector(-0.5, -0.3, 0), Vector(1));

    Scene scene;
    scene.setCameraPosition(Vector(0, 0, 0));
    scene.addLight(light);
    scene.addPrimitive(new Sphere(Vector(-0.21, -0.2, -1.2), 0.2, Vector(0.9, 0, 0)));
    scene.addPrimitive(new Sphere(Vector(0.21, -0.2, -1.2), 0.2, Vector(0.2, 0.5, 0.9)));
    scene.addPrimitive(new Sphere(Vector(0, 0.2, -1.2), 0.2, Vector(0.55, 0.9, 0)));
    scene.addPrimitive(new Plane(Vector(0, -0.4, 0), Vector(0, 1, 0), Vector(0.2)));

    std::cout << "Scene ready, starting rendering..." << std::endl;

    std::chrono::system_clock::time_point begin = std::chrono::system_clock::now();

    auto *image = Tracer().render(screen, scene, Shader());

    std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - begin;

    std::cout << "Rendering finished in time (s): " << elapsed_seconds.count() << std::endl;

    std::cout << "Saving to file" << std::endl;

    std::ofstream ofs("./image.ppm", std::ios::out | std::ios::binary);
    ofs << "P3\n" << width << " " << height << "\n255\n";
    for (unsigned i = 0; i < width * height; ++i) {
        ofs << floor(fmax(0, image[i].x) * 255) << " "
            << floor(fmax(0, image[i].y) * 255) << " "
            << floor(fmax(0, image[i].z) * 255) << " ";
    }
    ofs.close();

    delete[] image;

    std::cout << "File saved" << std::endl;

    return 0;
}