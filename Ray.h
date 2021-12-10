#ifndef RTSIM_RAY_H
#define RTSIM_RAY_H

#include "Vector.h"

class Ray {
public:
    Ray() = default;
    Ray(const P3& origin, const V3& direction) : orig(origin), dir(unit(direction)) {};
    P3 origin() const {return orig;}
    V3 direction() const {return dir;}
    P3 operator()(double time) const {
        return orig + time*dir;
    }
    P3 origin() {
        return static_cast<Vector>(orig);
    }
    V3 direction() {
        return static_cast<Vector>(dir);
    }
private:
    P3 orig;
    V3 dir;
};

#endif //RTSIM_RAY_H
