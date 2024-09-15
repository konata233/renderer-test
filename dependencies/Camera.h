//
// Created on 2024/9/14.
//

#ifndef RENDERER_CAMERA_H
#define RENDERER_CAMERA_H


#include "Vector.h"

class Camera {
public:
    Vector4<double> position;
    Vector4<double> look_at;
    Vector4<double> up;
};


#endif //RENDERER_CAMERA_H
