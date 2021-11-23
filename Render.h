#ifndef RTSIM_RENDER_H
#define RTSIM_RENDER_H

#include <iostream>
#include <fstream>
#include "Camera.h"
#include "RGB.h"
#include "Ray.h"
#include "Vector.h"
#include "Scene.h"
using namespace std;

void render(Camera cam, Scene scene) {
    std::cout << "Rendering" << std::endl;

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
            for (auto object: scene._objects) {
                auto t = object->intersect(r);
                if (t > 0.0) {
                    V3 normal = unit(r(t) - object->_position);
                    for (auto source: scene._sources) {
                        auto light_vector = (source->_position - r(t));
                        //auto light_intensity = source->_intensity / (light_vector.length() * light_vector.length());
                        double light_intensity = dot(unit(light_vector), unit(normal));
                        pixel_color = object->_color * light_intensity;
                    }
                }
            }
            write_RGB(output, pixel_color);

        }
    }
    output.close();
}

#endif //RTSIM_RENDER_H
