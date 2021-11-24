#ifndef RTSIM_RENDER_H
#define RTSIM_RENDER_H

#define AMBIENT_COEF 0.05

#define INFTY 1e10

#include <iostream>
#include <fstream>
#include <map>
#include "Camera.h"
#include "RGB.h"
#include "Ray.h"
#include "Vector.h"
#include "Scene.h"
using namespace std;

double specular(V3 reflection_ray, V3 source_ray) {
    auto light_intensity = (dot(unit(source_ray), unit(reflection_ray)));
    if (light_intensity < 0) {
        // Clamped
        light_intensity = 0;
    }
    return light_intensity;
}

double diffuse(V3 normal_ray, V3 source_ray) {
    auto light_intensity = dot(unit(source_ray), unit(normal_ray));
    if (light_intensity < 0) {
        // Clamped
        light_intensity = 0;
    }
    return light_intensity;
}

auto hitList(Ray ray, Scene scene) {
    map<Object*, double> hit_list;
    for (auto object : scene._objects) {
        hit_list.insert(make_pair(object, object->intersect(ray, 0, INFTY)));
    }
    return hit_list;
}

void render(Camera cam, Scene scene) {
    std::cout << "Rendering scene..." << std::endl;

    ofstream output;
    output.open ("image.ppm");
    output << "P3" << endl;
    output << cam.image_width << " " << cam.image_height << endl;
    output << "255" << endl;

    for (int j = cam.image_height-1; j >=0; --j) {
        for (int i = 0; i < cam.image_width; ++i) {
            // Rendering
            auto u = double(i) / double(cam.image_width-1);
            auto v = double(j) / double(cam.image_height-1);
            Ray r(cam.origin, cam.lower_left_corner + u * cam.horizontal + v * cam.vertical - cam.origin);
            RGB pixel_color(0, 0, 0);
            auto hit_list = hitList(r, scene);
            using Iter = std::map<Object*, double>::iterator;
            // TODO: fix crash on empty scene
            auto it = min_element(hit_list.begin(), hit_list.end(), [](const pair<Object*, double> &lhs, const pair<Object*, double> &rhs) {
                auto l = lhs.second < 0 ? numeric_limits<double>::max() : lhs.second;
                auto r = rhs.second < 0 ? numeric_limits<double>::max() : rhs.second;
                return l < r;
            });
            Object* object = it->first;
            double t = it->second;
            if (t > 0.0) {
                //V3 p = r(t);
                V3 normal = unit(r(t) - object->_position);
                for (auto source: scene._sources) {
                    // Specular
                    auto light_vector = (source->_position - r(t));
                    auto reflection_ray = unit(reflect(r(t),normal));
                    double specular_intensity = object->_reflectivity * specular(reflection_ray, light_vector);
                    // Diffuse
                    double diffuse_intensity = (1-object->_reflectivity) * diffuse(normal, light_vector);
                    double ambient_intensity = AMBIENT_COEF;
                    pixel_color += ((source->_intensity * (specular_intensity + diffuse_intensity)) + ambient_intensity) * object->_color;
                }
            }
            write_RGB(output, pixel_color);

        }
    }
    output.close();
}

#endif //RTSIM_RENDER_H
