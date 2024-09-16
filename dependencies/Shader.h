//
// Created on 2024/9/15.
//

#ifndef RENDERER_SHADER_H
#define RENDERER_SHADER_H

#include "Color.h"
#include "Vertex.h"

template <class T>
class FragmentShader {
    Vertex<T>* vertices;

    FragmentShader(Vertex<T>* vs); // todo
};


#endif //RENDERER_SHADER_H
