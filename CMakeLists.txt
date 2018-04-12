# cmake_minimum_required(VERSION <specify CMake version here>)
project(rival_dealer)

set(CMAKE_CXX_STANDARD 17)

add_executable(rival_dealer main.cpp
        physics/Ray.cpp physics/Ray.h
        math/Vector.cpp math/Vector.h
        primitives/Sphere.cpp primitives/Sphere.h
        physics/Light.cpp physics/Light.h
        Tracer.cpp Tracer.h Screen.cpp
        Screen.h Scene.cpp Scene.h Shader.cpp
        Shader.h primitives/Primitive.h
        primitives/Plane.cpp primitives/Plane.h
        math/Util.h)