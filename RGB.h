#ifndef RTSIM_RGB_H
#define RTSIM_RGB_H

#include "Vector.h"

#include <iostream>

double clamp (double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

void write_RGB(std::ostream& out, RGB rgb) {
    out << static_cast<int>(255.0 * clamp(rgb.x(), 0.0, 0.999)) << ' '
        << static_cast<int>(255.0 * clamp(rgb.y(), 0.0, 0.999)) << ' '
        << static_cast<int>(255.0 * clamp(rgb.z(), 0.0, 0.999)) << '\n';
}


#endif //RTSIM_RGB_H
