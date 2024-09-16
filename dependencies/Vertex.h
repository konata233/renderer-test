//
// Created on 2024/9/15.
//

#ifndef RENDERER_VERTEX_H
#define RENDERER_VERTEX_H


#include "Vector.h"
#include "Matrix.h"

template <class T>
class Vertex;

template <class T>
class VertexShader;


template <class T>
class Vertex {
public:
    Vertex<T>* apply_primary_transform(Matrix<T> transform);

    Vertex<T>* apply_viewport_transform(Matrix<T> viewport);

    Vertex<T>* apply_shader(VertexShader<T> s);

    Vertex();

    Vertex(const Vector4<T>& pos);

protected:
    Vector4<T> pos;

    Vector4<T> primary;

    Vector4<T> final;

    VertexShader<T> shader;

};

template <class T>
Vertex<T>* Vertex<T>::apply_primary_transform(Matrix<T> transform) {
    this->primary = transform * this->pos;
    return this;
}

template <class T>
Vertex<T>* Vertex<T>::apply_shader(VertexShader<T> s) {
    this->shader = s;
    return this;
}

template <class T>
Vertex<T>* Vertex<T>::apply_viewport_transform(Matrix<T> viewport) {
    this->final = viewport * this->primary;
    return this;
}

template <class T>
Vertex<T>::Vertex(const Vector4<T>& pos) {
    this->pos = pos;
    this->primary = vec4t(0, 0, 0, 1);
    this->final = vec4t(0, 0, 0, 1);
    this->shader = NULL;
}

template <class T>
Vertex<T>::Vertex() {
    this->pos = vec4t(0, 0, 0, 1);
    this->primary = vec4t(0, 0, 0, 1);
    this->final = vec4t(0, 0, 0, 1);
    this->shader = NULL;
}


template <class T>
class VertexShader {
public:
    Vertex<T>* vertex;

    Color (* prog)(Vertex<T>* vert);

    const Color* apply();

    void reset();

    VertexShader(Vertex<T>* vert, Color (* prog)(Vertex<T>* v));

protected:
    Color buffer;
    bool buffer_available;
};

template <class T>
void VertexShader<T>::reset() {
    this->buffer_available = false;
}

template <class T>
const Color* VertexShader<T>::apply() {
    if (buffer_available) {
        return &this->buffer;
    } else {
        this->buffer = this->prog(this->vertex);
        this->buffer_available = true;
    }
}

template <class T>
VertexShader<T>::VertexShader(Vertex<T>* vert, Color (* prog)(Vertex<T>*)) {
    this->prog = prog;
    this->vertex = vert;
    this->buffer = Color();
    this->buffer_available = false;
}


#endif //RENDERER_VERTEX_H
