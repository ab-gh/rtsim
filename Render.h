#ifndef RTSIM_RENDER_H
#define RTSIM_RENDER_H

#define AMBIENT_COEF 0.09
#define DIFFUSE_COEF 1
#define SPECULAR_COEF 1
#define REFLECTION_COEF 0.8

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

// Prototype
RGB intensity(Scene, Ray, RGB);

// Track what objects the ray line will hit
auto hitList(Ray ray, Scene scene) {
    // Create map for objects hit and their distance
    map<Object*, double> hit_list;
    for (auto object : scene._objects) {
        // Find intersections between 0 and infinity
        hit_list.insert(make_pair(object, object->intersect(ray, 0, INFTY)));
    }
    return hit_list;
}

// Specular scattering
double specular(V3 reflection_ray, V3 source_ray) {
    // K_s (v_r . p_rs)^ys I_0
    // TODO: add ^ys
    auto light_intensity = (dot(unit(source_ray), unit(reflection_ray)));
    if (light_intensity < 0) {
        // Clamped
        light_intensity = 0;
    }
    return light_intensity;
}

// Diffuse scattering
double diffuse(V3 normal_ray, V3 source_ray) {
    // K_d (n_s . p_rs)^yd I_0
    // TODO: add ^yd
    auto light_intensity = dot(unit(source_ray), unit(normal_ray));
    if (light_intensity < 0) {
        // Clamped
        light_intensity = 0;
    }
    return light_intensity;
}

// Reflected light
RGB reflected(V3 reflection_ray, P3 reflection_point, Scene scene, RGB pixel_color) {
    Ray reflected_ray(reflection_point, reflection_ray);
    auto hit_list = hitList(reflected_ray, scene);
    auto it = min_element(hit_list.begin(), hit_list.end(), [](const pair<Object*, double> &lhs, const pair<Object*, double> &rhs) {
        // Send objects to infinity if they are not hit
        auto l = lhs.second <= 0 ? numeric_limits<double>::max() : lhs.second;
        auto r = rhs.second <= 0 ? numeric_limits<double>::max() : rhs.second;
        return l < r;
    });
    Object* object = it->first;
    double t = it->second;
    // If an object is not hit, return black
    if (t > 0) {
        return intensity(scene, reflected_ray, pixel_color);
    } else {
        return RGB(0, 0, 0);
    }
}



void progress(int j, double height) {
    double percent = fabs((j-height) / height) * 100;
    int p = static_cast<int>(percent);
    cout << "\rRendering scene... " << p << "% complete" << flush;
}

__map_iterator <__tree_iterator <__value_type <Object *, double>, __tree_node <__value_type <Object *, double>, void *> *, long>> get_closest(map<Object*, double> hit_list) {
    auto it = min_element(hit_list.begin(), hit_list.end(), [](const pair<Object*, double> &lhs, const pair<Object*, double> &rhs) {
        // Send objects to infinity if they are not hit
        auto l = lhs.second < 0 ? numeric_limits <double>::max ( ) : lhs.second;
        auto r = rhs.second < 0 ? numeric_limits <double>::max ( ) : rhs.second;
        return l < r;
    });
    return it;
}

RGB intensity(Scene scene, Ray r, RGB pixel_color) {
    // Generate list of objects hit by ray
    auto hit_list = hitList(r, scene);
    auto it = get_closest(hit_list);
    Object* object = it->first;
    double t = it->second;
    // If object is in front of camera
    if (t > 0.0) {
        //V3 p = r(t);
        // Calculate normal to surface
        V3 normal = object->normal(r(t));
        // Loop over all illumination sources
        for (auto source: scene._sources) {
            // Specular
            auto light_vector = (source->_position - r(t));
            auto reflection_ray = unit(reflect(r(t),normal));
            double specular_intensity = object->_reflectivity * specular(reflection_ray, light_vector) * SPECULAR_COEF;
            // Diffuse
            double diffuse_intensity = (1-object->_reflectivity) * diffuse(normal, light_vector) * DIFFUSE_COEF;
            double ambient_intensity = AMBIENT_COEF;
            // Reflected
            RGB reflected_light = object->_reflectivity * reflected(reflection_ray, r(t), scene, pixel_color) * REFLECTION_COEF;
            // Add to pixel color
            pixel_color += (reflected_light + (((source->_intensity * (specular_intensity + diffuse_intensity)) + ambient_intensity) * object->_color));
        }
    }
    return pixel_color;
}

void render(Camera cam, Scene scene) {
    // Open ppm file
    ofstream output;
    output.open ("image.ppm");
    // Write header
    output << "P3" << endl;
    output << cam.image_width << " " << cam.image_height << endl;
    output << "255" << endl;

    // Loop through each pixel
    for (int j = cam.image_height-1; j >=0; --j) {
        progress(j, cam.image_height);
        for (int i = 0; i < cam.image_width; ++i) {
            // Rendering
            auto u = double(i) / double(cam.image_width-1);
            auto v = double(j) / double(cam.image_height-1);
            // Construct ray
            Ray r(cam.origin, cam.lower_left_corner + u * cam.horizontal + v * cam.vertical - cam.origin);
            // Find the closest object
            // TODO: fix crash on empty scene
            // TODO: refactor min_element selection out
            // TODO: add backdrop function?
            RGB pixel_color = intensity(scene, r, RGB(0, 0, 0));
            // Clamp and write colour
            write_RGB(output, pixel_color);

        }
    }
    output.close();
}

#endif //RTSIM_RENDER_H
