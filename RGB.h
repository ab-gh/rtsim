#ifndef RTSIM_RGB_H
#define RTSIM_RGB_H

#include "Vector.h"

#include <iostream>

void write_RGB(std::ostream& out, RGB rgb) {
    out << static_cast<int>(255.999 * rgb.x()) << ' '
        << static_cast<int>(255.999 * rgb.y()) << ' '
        << static_cast<int>(255.999 * rgb.z()) << '\n';
}


#endif //RTSIM_RGB_H
