#ifndef RTSIM_RGB_H
#define RTSIM_RGB_H

#include "Vector.h"

#include <iostream>

// Clamp the values to a min and max
double clamp (double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

// Output RGB values to PPM file stream, clamped between 0 and slightly less than 255
void write_RGB(std::ostream& out, RGB rgb) {
    out << static_cast<int>(255.0 * clamp(rgb.x(), 0.0, 0.999)) << ' '
        << static_cast<int>(255.0 * clamp(rgb.y(), 0.0, 0.999)) << ' '
        << static_cast<int>(255.0 * clamp(rgb.z(), 0.0, 0.999)) << '\n';
}


#endif //RTSIM_RGB_H
