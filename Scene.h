#ifndef RTSIM_SCENE_H
#define RTSIM_SCENE_H

#include <vector>
#include "Object.h"
#include "Source.h"
#include <string>
#include <fstream>
#include <iostream>

enum shapes {
    _InfinitePlane,
    _Sphere,
    _Cone,
    _Disc
};

shapes hash(std::string s){
    if (s == "InfinitePlane") {
        return _InfinitePlane;
    } else if (s == "Sphere") {
        return _Sphere;
    } else if (s == "Cone") {
        return _Cone;
    } else if (s == "Disc") {
        return _Disc;
    }
}

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
    void save(std::string file) {
        std::ofstream fout(file);
        fout << "objects:" << std::endl;
        for (auto object : this->_objects) {
            object->serialize(fout);
        }
        fout << "sources:" << std::endl;
        for (auto source : this->_sources) {
            source->serialize(fout);
        }
        fout << "EOF:" << std::endl;
        fout.close();
    }
    void read(std::string file) {
        std::ifstream fin(file);
        std::string line;
        while (std::getline(fin, line)) {
            if (line == "objects:") {
                while (std::getline(fin, line)) {
                    if (line == "sources:") {
                        break;
                    }
                    if (line == "{") {
                        continue;
                    }
                    std::string type = line.substr(0, line.find(":"));
                    std::string s = " -";
                    type.erase(0, s.length());

                    std::string construction = line.erase(0, line.find(":")+3);
                    switch (hash(type)) {
                        case _InfinitePlane:
                            this->addObject(new InfinitePlane(construction));
                            break;
                        case _Sphere:
                            this->addObject(new Sphere(construction));
                            break;
                        case _Cone:
                            this->addObject(new Cone(construction));
                            break;
                        case _Disc:
                            this->addObject(new Disc(construction));
                            break;
                    }
                }
            }
            if (line == "sources:") {
                while (std::getline(fin, line)) {
                    if (line == "EOF:") {
                        break;
                    }
                    std::string construction = line.erase(0, line.find(":")+3);
                    this->addSource(new Source(construction));
                }
            }
        }
    }
};

#endif //RTSIM_SCENE_H
