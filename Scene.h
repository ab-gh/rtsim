#ifndef RTSIM_SCENE_H
#define RTSIM_SCENE_H

#include <vector>
#include "Object.h"
#include "Source.h"
#include <string>
#include <fstream>

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
        fout << "objects: " << std::endl;
        for (auto object : this->_objects) {
            object->serialize(fout);
        }
        fout << "sources: " << std::endl;
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
                    Object* object = new Object();
                    object->deserialize(line);
                    this->_objects.push_back(object);
                }
            }
            if (line == "sources:") {
                while (std::getline(fin, line)) {
                    if (line == "EOF:") {
                        break;
                    }
                    Source* source = new Source();
                    source->deserialize(line);
                    this->_sources.push_back(source);
                }
            }
        }
    }
};

#endif //RTSIM_SCENE_H
