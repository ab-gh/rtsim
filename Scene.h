#ifndef RTSIM_SCENE_H
#define RTSIM_SCENE_H

#include <vector>
#include "Object.h"
#include "Source.h"

class Scene {
public:
    std::vector <Object*> _objects;
    std::vector <Source*> _sources;
public:
    Scene() = default;
    ~Scene() = default;
    void addObject(Object* object) {
        this->_objects.push_back(object);
    }
    void addSource(Source* source) {
        this->_sources.push_back(source);
    }
};

#endif //RTSIM_SCENE_H
