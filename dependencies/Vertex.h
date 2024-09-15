//
// Created on 2024/9/15.
//

#ifndef RENDERER_VERTEX_H
#define RENDERER_VERTEX_H


#include "Vector.h"
#include "Matrix.h"

template <class T>
class Vertex {
public:
    Vector4<T> pos;

    Vector4<T> transformed;

    Vertex<T>* apply_transform(Matrix<T> mat);

    Vertex();

    Vertex(const Vector4<T>& pos);
};

template <class T>
Vertex<T>* Vertex<T>::apply_transform(Matrix<T> mat) {
    this->transformed = mat * this->pos.copy();
}

template <class T>
Vertex<T>::Vertex(const Vector4<T>& pos) {
    this->pos = pos.copy();
    this->transformed = vec4t(0, 0, 0, 1);
}

template <class T>
Vertex<T>::Vertex() {
    this->pos = vec4t(0, 0, 0, 1);
    this->transformed = vec4t(0, 0, 0, 1);
}


#endif //RENDERER_VERTEX_H
