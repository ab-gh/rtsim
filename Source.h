#ifndef RTSIM_SOURCE_H
#define RTSIM_SOURCE_H

#include "Vector.h"

class Source {
public:
    Source(V3 position, double intensity) {
        this->_position = position;
        this->_intensity = intensity;
    }
    ~Source() = default;
    void serialize(std::ostream &os) const {
        os << "- Source: {" << std::endl;
        os << "position: " << str(this->_position) << "," <<  std::endl;
        os << "intensity: " << this->_intensity << ","  << std::endl;
        os << "}" << std::endl;
    }
public:
    P3 _position;
    double _intensity;
};

#endif //RTSIM_SOURCE_H
