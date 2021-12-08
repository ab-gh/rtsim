#ifndef RTSIM_SOURCE_H
#define RTSIM_SOURCE_H

#include "Vector.h"

class Source {
public:
    Source(V3 position, double intensity) {
        this->_position = position;
        this->_intensity = intensity;
    }
    Source(std::string construction) {
        auto params = explode(construction, ';');
        this->_position = V3(params[0]);
        this->_intensity = stod(params[1]);
    }
    ~Source() = default;
    void serialize(std::ostream &os) const {
        os << "- Source: {";
        os << str(this->_position) << ";";
        os << this->_intensity << ";";
        os << "}" << std::endl;
    }
public:
    P3 _position;
    double _intensity;
};

#endif //RTSIM_SOURCE_H
