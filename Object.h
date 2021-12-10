#include "Vector.h"
#include "Ray.h"
#include <vector>

#ifndef RTSIM_OBJECT_H
#define RTSIM_OBJECT_H


class Object {
public:
    // Default constructor
    Object() = default;
    // Deserialization constructor
    Object(std::string);
    // Mark as virtual to force abstract class
    virtual ~Object() = default;
    // Intersection function
    virtual std::pair<double, const Object*> intersect(const Ray &ray, double min, double max) const = 0;
    // Normal function
    virtual V3 normal(const V3 &point) const = 0;
    // Serializer
    virtual void serialize(std::ostream &os) const = 0;
public:
    V3 _position;
    RGB _color;
    double _reflectivity;
};
// Sphere
// _position: Position of the center of the sphere
// _radius: Radius of the sphere
// _color: Color of the sphere
// _reflectivity: Reflectivity of the sphere
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
    Sphere(std::string construction) {
        auto params = explode(construction, ';');
        this->_position = V3(params[0]);
        this->_radius = stod(params[1]);
        this->_color = RGB(params[2]);
        this->_reflectivity = stod(params[3]);
    }
    ~Sphere() = default;
    void serialize(std::ostream &os) const override {
        os << "- Sphere: {";
        os << str(this->_position) << ";";
        os << this->_radius << ";";
        os << str(this->_color) << ";";
        os << this->_reflectivity << ";";
        os << "}" << std::endl;
    }
    V3 normal(const V3 &point) const override {
        return unit(point - this->_position);
    }
    std::pair<double, const Object*> intersect(const Ray &ray, double min, double max) const override {
        V3 oc = ray.origin() - _position;
        // Construct quadratic equation
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
            // Min max are currently unused
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
// _position: Position of the plane (can be any point on the plane)
// _normal: Normal of the plane (defines "direction" of the plane)
// _color: Color of the plane
// _reflectivity: Reflectivity of the plane
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
    InfinitePlane(std::string construction) {
        auto params = explode(construction, ';');
        this->_position = V3(params[0]);
        this->_normal = V3(params[1]);
        this->_color = RGB(params[2]);
        this->_reflectivity = stod(params[3]);
    }
    ~InfinitePlane() = default;
    void serialize(std::ostream &os) const override {
        os << "- InfinitePlane: {";
        os << str(this->_position) << ";";
        os << str(this->_normal) << ";";
        os << str(this->_color) << ";";
        os << this->_reflectivity << ";";
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

// Disc
// _position: Position of the center of the disc
// _normal: Normal of the disc (defines "direction" of the disc)
// _radius: Radius of the disc
// _color: Color of the disc
// _reflectivity: Reflectivity of the disc
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
    Disc(std::string construction) {
        auto params = explode(construction, ';');
        this->_position = V3(params[0]);
        this->_normal = V3(params[1]);
        this->_radius = stod(params[2]);
        this->_color = RGB(params[3]);
        this->_reflectivity = stod(params[4]);
    }
    ~Disc() = default;
    void serialize(std::ostream &os) const override {
        os << "- Disc: {";
        os << str(this->_position) << ";";
        os << str(this->_normal) << ";";
        os << this->_radius << ";";
        os << str(this->_color) << ";";
        os << this->_reflectivity << ";";
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
                // Inside the radius
                return std::make_pair( (dist), this);
            } else {
                // Outside the radius
                return std::make_pair( -1.0, this);
            }
        }
    }
};

// Cone
// _position: Position of the apex of the cone (the tip)
// _normal: Center point of the cone's circular base
// _radius: Radius of the cone's circular base
// _color: Color of the cone
// _reflectivity: Reflectivity of the cone
// _cap: The circular cap at the end of the cone (linked to a Disc)
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
    Cone(std::string construction) {
        auto params = explode(construction, ';');
        this->_position = V3(params[0]);
        this->_base = V3(params[1]);
        this->_radius = stod(params[2]);
        this->_color = RGB(params[3]);
        this->_reflectivity = stod(params[4]);
        V3 cap_normal = unit(_base - _position);
        this->_cap = Disc(_base, cap_normal, _radius, _color, _reflectivity);
    }
    ~Cone() = default;
    void serialize(std::ostream &os) const override {
        os << "- Cone: {";
        os << str(this->_position) << ";";
        os << str(this->_base) << ";";
        os << this->_radius << ";";
        os << str(this->_color) << ";";
        os << this->_reflectivity << ";";
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

        // Construct the quadratic equation
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
                // Normal hit
                root = -(b / (2 * a));
            } else {
                // Ray is tangent to the cone
                return std::make_pair( root, this);
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
        // Point of intersection ray
        auto Lint = ray.origin() + (root * unit(ray.direction()));
        // Test if the point has hit the base cap
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
