#include "Vector.h"
#include "Ray.h"

#ifndef RTSIM_OBJECT_H
#define RTSIM_OBJECT_H


class Object {
public:
    Object() = default;
    virtual ~Object() = default;
    virtual std::pair<double, const Object*> intersect(const Ray &ray, double min, double max) const = 0;
    virtual V3 normal(const V3 &point) const = 0;
    virtual void serialize(std::ostream &os) const = 0;
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
    void serialize(std::ostream &os) const override {
        os << "- Sphere: {" << std::endl;
        os << "position: " << str(this->_position) << "," <<  std::endl;
        os << "radius: " << this->_radius << ","  << std::endl;
        os << "color: " << str(this->_color) << ","  << std::endl;
        os << "reflectivity: " << this->_reflectivity << ","  << std::endl;
        os << "}" << std::endl;
    }
    V3 normal(const V3 &point) const override {
        return unit(point - this->_position);
    }
    std::pair<double, const Object*> intersect(const Ray &ray, double min, double max) const override {
        V3 oc = ray.origin() - _position;
        auto a = dot(ray.direction(), ray.direction());
        auto b_div_2 = dot(oc, ray.direction());
        auto c = powf(oc.length(), 2) - _radius * _radius;
        auto discriminant = b_div_2 * b_div_2 - a * c;
        if (discriminant < 0) {
            // No Hit
            return std::make_pair( -1.0, this);
        } else {
            auto sqrt_discriminant = sqrt(discriminant);
            auto root = (-b_div_2 - sqrt_discriminant) / a;
            if (root < min || max < root) {
                root = (-b_div_2 + sqrt_discriminant) / a;
                if (root < min || max < root) {
                    // No Hit
                    return std::make_pair( -1.0, this);
                }
            }
            return std::make_pair( root, this);
        }
    }

};

// Infinite Plane
class InfinitePlane : public Object {
protected:
    V3 _normal;
public:
    InfinitePlane() {};
    InfinitePlane(V3 position, V3 normal, RGB colour, double reflectivity) : Object() {
        this->_position = position;
        this->_normal = normal;
        this->_color = colour;
        this->_reflectivity = reflectivity;
    }
    ~InfinitePlane() = default;
    void serialize(std::ostream &os) const override {
        os << "- InfinitePlane: {" << std::endl;
        os << "position: " << str(this->_position) << ","  << std::endl;
        os << "normal: " << str(this->_normal) << ","  << std::endl;
        os << "color: " << str(this->_color) << ","  << std::endl;
        os << "reflectivity: " << this->_reflectivity << ","  << std::endl;
        os << "}" << std::endl;
    }
    V3 normal(const V3 &point) const override {
        return _normal;
    }

    std::pair<double, const Object*> intersect(const Ray &ray, double min, double max) const override {
        auto denom = dot(unit(ray.direction()), unit(_normal));
        auto dist = dot(_position - ray.origin(), unit(_normal)) / denom;
        if (dist < min || max < dist) {
            return std::make_pair( -1.0, this);
        }
        return std::make_pair( fabs(dist), this);
    }
};

class Disc : public InfinitePlane {
private:
    double _radius;
public:
    Disc() {};
    Disc(V3 position, V3 normal, double radius, RGB colour, double reflectivity) : InfinitePlane(position, normal, colour, reflectivity) {
        this->_position = position;
        this->_normal = normal;
        this->_radius = radius;
        this->_color = colour;
        this->_reflectivity = reflectivity;
    }
    ~Disc() = default;
    void serialize(std::ostream &os) const override {
        os << "- Disc: {" << std::endl;
        os << "position: " << str(this->_position) << ","  << std::endl;
        os << "normal: " << str(this->_normal) << ","  << std::endl;
        os << "radius: " << this->_radius << ","  << std::endl;
        os << "color: " << str(this->_color) << ","  << std::endl;
        os << "reflectivity: " << this->_reflectivity << ","  << std::endl;
        os << "}" << std::endl;
    }
    V3 normal(const V3 &point) const override {
        return _normal;
    }
    std::pair<double, const Object*> intersect(const Ray &ray, double min, double max) const override {
        // Plane intersection
        auto denom = dot(unit(ray.direction()), unit(_normal));
        auto dist = dot(_position - ray.origin(), unit(_normal)) / denom;
        if (dist < min || max < dist) {
            return std::make_pair( -1.0, this);
        } else {
            V3 p = ray.origin() + ray.direction()*fabs(dist);
            V3 v = p - _position;
            auto d2 = dot(v, v);
            if (d2 <= pow(_radius, 2)) {
                // Iniside the radius
                return std::make_pair( (dist), this);
            } else {
                // Outside the radius
                return std::make_pair( -1.0, this);
            }
        }
    }
};
// Cone
class Cone : public Object {
private:
    V3 _base;
    double _radius;
    Disc _cap;
public:
    Cone(V3 position, V3 base, double radius, RGB colour, double reflectivity) : Object() {
        this->_position = position;
        this->_base = base;
        this->_radius = radius;
        this->_color = colour;
        this->_reflectivity = reflectivity;
        V3 cap_normal = unit(base - position);
        this->_cap = Disc(base, cap_normal, radius, colour, reflectivity);
    }
    ~Cone() = default;
    void serialize(std::ostream &os) const override {
        os << "- Cone: {" << std::endl;
        os << "position: " << str(this->_position) << ","  << std::endl;
        os << "base: " << str(this->_base) << ","  << std::endl;
        os << "radius: " << this->_radius << ","  << std::endl;
        os << "color: " << str(this->_color) << ","  << std::endl;
        os << "reflectivity: " << this->_reflectivity << ","  << std::endl;
        os << "}" << std::endl;
    }
    V3 normal(const V3 &point) const override {
        auto Vx = point.x() - _position.x();
        auto Vz = point.z() - _position.z();
        auto V = unit(V3(Vx, 0, Vz));

        auto Nx = V.x()*(_position - _base).length()/_radius;
        auto Nz = V.z()*(_position - _base).length()/_radius;
        auto Ny = _radius/(point - _base).length();
        return V3(Nx, Ny, Nz);

    }
    std::pair<double, const Object*>  intersect(const Ray &ray, double min, double max) const override {
        double root;
        double otherroot;
        V3 H = _base - _position;
        V3 hhat = unit(H);
        V3 v = ray.direction();
        V3 w = ray.origin() - _position;
        auto m = powf(_radius, 2) / powf(H.length(), 2);

        auto a = dot(v,v) - (m * pow(dot(v, hhat), 2)) - pow(dot(v, hhat), 2);
        auto b = 2 * (dot(v,w) - (m * dot(v, hhat) * dot(w, hhat) )- (dot(v, hhat) * dot(w, hhat) ));
        auto c = dot(w,w) - (m*pow(dot(w, hhat), 2)) - pow(dot(w, hhat), 2);

        auto discriminant = b*b - 4*a*c;

        auto cosalpha = H.length()/sqrt(H.length()*H.length() + _radius*_radius);
        auto dotvh = fabs(dot(unit(v), hhat));
        if (discriminant < 0) {
            // No Hit
            return std::make_pair( -1.0, this);
        } else if (discriminant == 0) {
            if (dotvh != cosalpha) {
                root = -(b / (2 * a));
            } else {
                // Infinite hits, so assume none
                return std::make_pair( root, this);
            }
        } else if (discriminant > 0) {
            auto root1 = (-b + sqrt(discriminant)) / (2 * a);
            auto root2 = (-b - sqrt(discriminant)) / (2 * a);
            if (root1 < root2) {
                root = root1;
                otherroot = root2;
            } else {
                root = root2;
                otherroot = root1;
            }
        }
        auto Lint = ray.origin() + (root * unit(ray.direction()));
        auto intersect_test = dot((Lint - _position), hhat);
        if (intersect_test > H.length()) {
            return _cap.intersect(ray, min, max);
        } else if (0 <= intersect_test && intersect_test <= H.length()) {
            return std::make_pair( root, this);
        } else {
            return std::make_pair (-1.0, this);
        }
    }
};

#endif //RTSIM_OBJECT_H
