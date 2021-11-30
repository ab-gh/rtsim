#include "Vector.h"
#include "Ray.h"

#ifndef RTSIM_OBJECT_H
#define RTSIM_OBJECT_H


class Object {
public:
    Object() = default;
    virtual ~Object() = default;
    virtual double intersect(const Ray &ray, double min, double max) const = 0;
public:
    V3 _position;
    RGB _color;
    double _reflectivity;
};

class Sphere : public Object {
private:
    double _radius;
public:
    Sphere(V3 position, double radius, RGB colour, double reflectivity) : Object() {
        this->_position = position;
        this->_radius = radius;
        this->_color = colour;
        this->_reflectivity = reflectivity;
    }
    ~Sphere() = default;
    double intersect(const Ray &ray, double min, double max) const {
        V3 oc = ray.origin() - _position;
        auto a = dot(ray.direction(), ray.direction());
        auto b_div_2 = dot(oc, ray.direction());
        auto c = powf(oc.length(), 2) - _radius * _radius;
        auto discriminant = b_div_2 * b_div_2 - a * c;
        if (discriminant < 0) {
            // No Hit
            return -1.0;
        } else {
            auto sqrt_discriminant = sqrt(discriminant);
            auto root = (-b_div_2 - sqrt_discriminant) / a;
            if (root < min || max < root) {
                root = (-b_div_2 + sqrt_discriminant) / a;
                if (root < min || max < root) {
                    // No Hit
                    return -1.0;
                }
            }
            return root;
        }
    }

};
// Infinite Plane

class InfinitePlane : public Object {
private:
    V3 _normal;
public:
    InfinitePlane(V3 position, V3 normal, RGB colour) : Object() {
        this->_position = position;
        this->_normal = normal;
        this->_color = colour;
        this->_reflectivity = 0;
    }
    ~InfinitePlane() = default;
    double intersect(const Ray &ray, double min, double max) const {
        auto denom = dot(unit(ray.direction()), unit(_normal));
        auto dist = dot(unit(_position - ray.origin()), unit(_normal)) / denom;
        if (dist < min || max < dist) {
            return -1.0;
        }
        return fabs(dist);
    }
};

// Cylinder


#endif //RTSIM_OBJECT_H
