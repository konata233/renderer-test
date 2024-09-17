//
// Created on 2024/9/15.
//

#ifndef RENDERER_SHADER_H
#define RENDERER_SHADER_H

#include "Color.h"
#include "Vertex.h"

template <class T>
class FragmentShaderContext {
public:
    Vertex<T>* vertices;

    Color color_interpolated;

    FragmentShaderContext() = default;

    FragmentShaderContext(Vertex<T>* verts, const Color& color);
};

template <class T>
FragmentShaderContext<T>::FragmentShaderContext(Vertex<T>* verts, const Color& color) {
    this->vertices = verts;
    this->color_interpolated = color;
}

template <class T>
class FragmentShader {
public:
    Color apply(Vertex<T>* vertices, Color& color_interpolated);

    explicit FragmentShader(Color (* prog)(FragmentShaderContext<T>& ctx));

    FragmentShader() = default;

protected:
    Color ( * prog)(FragmentShaderContext<T>& ctx){};
};

template <class T>
Color FragmentShader<T>::apply(Vertex<T>* vertices, Color& color_interpolated) {
    FragmentShaderContext<T> ctx = FragmentShaderContext<T>(vertices, color_interpolated);
    return this->prog(ctx);
}

template <class T>
FragmentShader<T>::FragmentShader(Color (* prog)(FragmentShaderContext<T>& ctx)) {
    this->prog = prog;
}


#endif //RENDERER_SHADER_H
