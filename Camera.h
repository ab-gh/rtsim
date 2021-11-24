//
// Created by ash on 23/11/2021.
//

#ifndef RTSIM_CAMERA_H
#define RTSIM_CAMERA_H

#include "Vector.h"

class Camera {
public:
    Camera() {
        this->aspect_ratio = 16.0/9.0;
        this->image_width = 1000;
        this->image_height = static_cast<int>(this->image_width / this->aspect_ratio);

        this->viewport_height = 2.0;
        this->viewport_width = this->viewport_height * this->aspect_ratio;

        this->focal_length = 1.0;

        this->origin = P3(0.0, 0.0, 0.0);
        this->horizontal = V3(this->viewport_width, 0.0, 0.0);
        this->vertical = V3(0.0, this->viewport_height, 0.0);
        this->lower_left_corner = this->origin - this->horizontal/2 - this->vertical/2 - V3(0, 0, this->focal_length);
    }

public:
    double aspect_ratio;
    double image_width;
    double image_height;

    double viewport_height;
    double viewport_width;

    double focal_length;

    P3 origin;
    V3 horizontal;
    V3 vertical;
    V3 lower_left_corner;

};

#endif //RTSIM_CAMERA_H
