#include "Vector.h"
#include "Ray.h"

#ifndef RTSIM_OBJECT_H
#define RTSIM_OBJECT_H


class Object {
public:
    Object() = default;
    virtual ~Object() = default;
    virtual double intersect(const Ray &ray, double min, double max) const = 0;
    virtual V3 normal(const V3 &point) = 0;
public:
    V3 _position;
    RGB _color;
    double _reflectivity;
};
// Sphere
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
    V3 normal(const V3 &point) override {
        return unit(point - this->_position);
    }
    double intersect(const Ray &ray, double min, double max) const override {
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
    InfinitePlane(V3 position, V3 normal, RGB colour, double reflectivity) : Object() {
        this->_position = position;
        this->_normal = normal;
        this->_color = colour;
        this->_reflectivity = reflectivity;
    }
    ~InfinitePlane() = default;
    V3 normal(const V3 &point) override {
        return _normal;
    }
    double intersect(const Ray &ray, double min, double max) const override {
        auto denom = dot(unit(ray.direction()), unit(_normal));
        auto dist = dot(_position - ray.origin(), unit(_normal)) / denom;
        if (dist < min || max < dist) {
            return -1.0;
        }
        return fabs(dist);
    }
};
// Cone
class Cone : public Object {
private:
    V3 _base;
    double _radius;
public:
    Cone(V3 position, V3 base, double radius, RGB colour, double reflectivity) : Object() {
        this->_position = position;
        this->_base = base;
        this->_radius = radius;
        this->_color = colour;
        this->_reflectivity = reflectivity;
    }
    ~Cone() = default;
    V3 normal(const V3 &point) override {
        auto Vx = point.x() - _position.x();
        auto Vz = point.z() - _position.z();
        auto V = unit(V3(Vx, 0, Vz));

        auto Nx = V.x()*(_position - _base).length()/_radius;
        auto Nz = V.z()*(_position - _base).length()/_radius;
        auto Ny = _radius/(point - _base).length();
        return V3(Nx, Ny, Nz);

    }
    double intersect(const Ray &ray, double min, double max) const override {
        double root;
        V3 H = _base - _position;
        V3 h = unit(H);
        V3 v = ray.direction();
        V3 w = ray.origin() - _position;
        auto m = pow(_radius, 2) / pow(H.length(), 2);

        auto a = dot(v,v) - m * pow(dot(v,h), 2) - pow(dot(v,h), 2);
        auto b = 2 * ( dot(v,w) - m*dot(v,h)*dot(w,h) - dot(v,h)*dot(w,h) );
        auto c = dot(w,w) - m*pow(dot(w,h), 2) - pow(dot(w,h), 2);

        auto discriminant = b*b - 4*a*c;

        auto cosalpha = H.length()/sqrt(H.length()*H.length() - _radius*_radius);
        auto dotvh = fabs(dot(unit(v),h));
        if (discriminant < 0) {
            // No Hit
            return -1.0;
        } else if (discriminant == 0) {
            if (dotvh != cosalpha) {
                root = -(b / (2 * a));
            } else {
                // Infinite hits, so assume none
                root = (b / (2 * a));
            }
        } else if (discriminant > 0) {
            auto root1 = (-b + sqrt(discriminant)) / (2 * a);
            auto root2 = (-b - sqrt(discriminant)) / (2 * a);
            if (root1 < root2) {
                root = root1;
            } else {
                root = root2;
            }
        }
        auto Lint = ray.origin() + root * ray.direction();
        auto intersect_test = dot((Lint - _position), h);
        if (intersect_test < 0) {
            return -1.0;
        } else if (intersect_test > H.length()) {
            return -1.0;
        } else {
            return root;
        }
    }
};
// Cylinder


#endif //RTSIM_OBJECT_H
