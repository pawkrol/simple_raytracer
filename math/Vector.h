#ifndef RIVAL_DEALER_VECTOR_H
#define RIVAL_DEALER_VECTOR_H

#include <string>

class Vector {

public:
    double x;
    double y;
    double z;

    Vector();
    explicit Vector(double v);
    Vector(double x, double y);
    Vector(double x, double y, double z);

    std::string print();

    void normalize();
    void max(double max);
    void min(double min);
    double dot(Vector v);
    Vector cross(Vector v);

    Vector operator-(Vector v);
    Vector operator-();
    Vector operator+(Vector v);
    Vector operator*(double v); //by scalar
    Vector operator*(Vector v); //by vector

    void operator+=(Vector v);

    static Vector normalize(Vector v);
    static Vector reflect(Vector i, Vector n);
};

#endif //RIVAL_DEALER_VECTOR_H
