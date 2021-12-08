#include <string>
#include <cmath>
#include <vector>
#ifndef RTSIM_VECTOR_H
#define RTSIM_VECTOR_H

std::vector<std::string> explode(const std::string& str, const char& ch) {
    std::string next;
    std::vector<std::string> result;

    for (std::string::const_iterator it = str.begin(); it != str.end(); it++) {
        // Terminal char
        if (*it == ch) {
            if (!next.empty()) {
                result.push_back(next);
                next.clear();
            }
        } else {
            next += *it;
        }
    }
    if (!next.empty())
        result.push_back(next);
    return result;
}

class Vector {
private:
    double vector[3];
public:
    Vector() : vector{0, 0, 0} {};
    Vector(double x, double y, double z) : vector{x, y, z} {};
    Vector(std::string str) {
        auto params = explode(str, ',');
        auto x = params[0].erase(0,1);
        auto y = params[1];
        auto z = params[2].erase((params[2]).length()-1, 1);
        vector[0] = stod(x);
        vector[1] = stod(y);
        vector[2] = stod(z);
    }
    // Getters
    [[nodiscard]] double x() const {return vector[0];}
    [[nodiscard]] double y() const {return vector[1];}
    [[nodiscard]] double z() const {return vector[2];}

    // Indexer
    double operator[](int index) const {return vector[index];}
    double& operator[](int index) {return vector[index];}

    // Maths
    Vector operator-() const { return {-vector[0], -vector[1], -vector[2]}; }
    Vector& operator+=(const Vector &v) {
        vector[0] += v.vector[0];
        vector[1] += v.vector[1];
        vector[2] += v.vector[2];
        return *this;
    }
    Vector& operator*=(const double m) {
        vector[0] *= m;
        vector[1] *= m;
        vector[2] *= m;
        return *this;
    }
    Vector& operator/=(const double m) {
        vector[0] /= m;
        vector[1] /= m;
        vector[2] /= m;
        return *this;
    }
    [[nodiscard]] double length() const {
        return sqrt(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);
    }
};

// Aliases
using V3 = Vector;
using P3 = Vector;
using RGB = Vector;

// Utilities

inline Vector operator+(const Vector &u, const Vector &v) {
    return {u.x() + v.x(), u.y() + v.y(), u.z() + v.z()};
}

inline Vector operator-(const Vector &u, const Vector &v) {
    return {u.x() - v.x(), u.y() - v.y(), u.z() - v.z()};

}

inline Vector operator*(const Vector &u, const Vector &v) {
    return {u.x() * v.x(), u.y() * v.y(), u.z() * v.z()};
}

inline Vector operator*(const Vector &u, const double m) {
    return {u.x() * m, u.y() * m, u.z() * m};
}

inline Vector operator*(const double m, const Vector &u) {
    return {u.x() * m, u.y() * m, u.z() * m};
}

inline Vector operator/(const Vector &u, const double m) {
    return {u.x() / m, u.y() / m, u.z() / m};
}

inline double dot(const Vector &u, const Vector &v) {
    return u.x() * v.x() + u.y() * v.y() + u.z() * v.z();
}

inline Vector cross(const Vector &u, const Vector &v) {
    return {u.y() * v.z() - u.z() * v.y(), u.z() * v.x() - u.x() * v.z(), u.x() * v.y() - u.y() * v.x()};
}

inline Vector unit(Vector u) {
    return u / u.length();
}

inline Vector reflect(const Vector &i, const Vector &n) {
    return i - 2 * dot(i, n) * n;
}

inline Vector refract(const Vector &i, const Vector &n, double eta) {
    auto cos_theta = fmin(dot(-i, n), 1.0);
    Vector out_perp = eta * (i + cos_theta * n);
    Vector out_para = -sqrt(fabs(1.0 - out_perp.length() * out_perp.length())) * n;
    return out_perp + out_para;
}

inline std::string str(const Vector &v) {
    return "(" + std::to_string(v.x()) + ", " + std::to_string(v.y()) + ", " + std::to_string(v.z()) + ")";
}

#endif //RTSIM_VECTOR_H
