#include "Vector.h"
#include "Ray.h"

#ifndef RTSIM_OBJECT_H
#define RTSIM_OBJECT_H


class Object {
public:
    Object() = default;
    virtual ~Object() = default;
    virtual double intersect(const Ray &ray/*, Vector &point, Vector &normal*/) const = 0;
public:
    V3 _position;
    RGB _color;
};

class Sphere : public Object {
private:
    double _radius;
public:
    Sphere(V3 position, double radius, RGB colour) {
        this->_position = position;
        this->_radius = radius;
        this->_color = colour;
    }
    virtual ~Sphere() = default;
    double intersect(const Ray &ray/*, double &t, V3 &normal, V3 &color*/) const {
        V3 oc = ray.origin() - _position;
        auto a = dot(ray.direction(), ray.direction());
        auto b = 2.0 * dot(oc, ray.direction());
        auto c = dot(oc, oc) - _radius * _radius;
        auto discriminant = b * b - 4 * a * c;
        if (discriminant < 0) {
            return -1.0;
        } else {
            return (-b - sqrt(discriminant) / (2.0 * a));
        }
    }

};


#endif //RTSIM_OBJECT_H
