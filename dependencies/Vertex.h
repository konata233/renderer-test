//
// Created on 2024/9/15.
//

#ifndef RENDERER_VERTEX_H
#define RENDERER_VERTEX_H


#include "Vector.h"
#include "Matrix.h"
#include "Color.h"

template <class T>
class Vertex;

template <class T>
class VertexShader;

template <class T>
class VertexShaderContext {
public:
    Vertex<T>* vert;

    VertexShaderContext() = default;

    explicit VertexShaderContext(Vertex<T>* v);
};

template <class T>
VertexShaderContext<T>::VertexShaderContext(Vertex<T>* v) {
    this->vert = v;
}

template <class T>
class Vertex {
public:
    Vertex<T>* apply_model_transform(Matrix<T>& transform);

    Vertex<T>* apply_primary_transform(Matrix<T>& transform);

    Vertex<T>* apply_viewport_transform(Matrix<T>& viewport);

    Vertex<T>* set_shader(VertexShader<T> s);

    const Color* get_color();

    Vertex();

    explicit Vertex(const Vector4<T>& pos);

    Vertex(const Vector4<T>& pos, VertexShader<T> s);

    Matrix<T> final;

    Matrix<T> primary;

    Vector4<T> pos;

protected:
    VertexShader<T> shader;

};

template <class T>
Vertex<T>* Vertex<T>::apply_model_transform(Matrix<T>& transform) {
    Matrix<T> transformed = transform * this->pos;
    this->pos.x = transformed.at_unsafe(0, 0);
    this->pos.y = transformed.at_unsafe(0, 1);
    this->pos.z = transformed.at_unsafe(0, 2);
    this->pos.w = 1;
    return this;
}

template <class T>
Vertex<T>::Vertex(const Vector4<T>& pos, VertexShader<T> s) {
    this->pos = pos;
    this->primary = mat4t(0, 0, 0, 1);
    this->final = mat4t(0, 0, 0, 1);
    this->shader = s;
}

template <class T>
const Color* Vertex<T>::get_color() {
    return this->shader.apply();
}

template <class T>
Vertex<T>* Vertex<T>::apply_primary_transform(Matrix<T>& transform) {
    this->primary = transform * this->pos;
    //std::cout << this->primary.pretty_print() << std::endl << "---------------------" << std::endl;
    return this;
}

template <class T>
Vertex<T>* Vertex<T>::set_shader(VertexShader<T> s) {
    this->shader = s;
    return this;
}

template <class T>
Vertex<T>* Vertex<T>::apply_viewport_transform(Matrix<T>& viewport) {
    this->final = viewport * this->primary;
    //std::cout << "final::" << this->final.pretty_print() << std::endl << "---------------------" << std::endl;
    return this;
}

template <class T>
Vertex<T>::Vertex(const Vector4<T>& pos) {
    this->pos = pos;
    this->primary = mat4t(0, 0, 0, 1);
    this->final = mat4t(0, 0, 0, 1);
    this->shader = VertexShader<T>();
}

template <class T>
Vertex<T>::Vertex() {
    this->pos = vec4t(0, 0, 0, 1);
    this->primary = vec4t(0, 0, 0, 1);
    this->final = vec4t(0, 0, 0, 1);
    this->shader = VertexShader<T>();
}


template <class T>
class VertexShader {
public:
    const Color* apply();

    void reset();

    VertexShader(Vertex<T>* vert, Color (* prog)(VertexShaderContext<T>& ctx));

    VertexShader() = default;

protected:
    Vertex<T>* vertex;

    Color (* prog)(VertexShaderContext<T>& vert);

    Color buffer;
    bool buffer_available{};
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
        VertexShaderContext ctx = VertexShaderContext(this->vertex);
        this->buffer = this->prog(ctx);
        this->buffer_available = true;
        return &this->buffer;
    }
}

template <class T>
VertexShader<T>::VertexShader(Vertex<T>* vert, Color (* prog)(VertexShaderContext<T>&)) {
    this->prog = prog;
    this->vertex = vert;
    this->buffer = Color();
    this->buffer_available = false;
}


#endif //RENDERER_VERTEX_H
