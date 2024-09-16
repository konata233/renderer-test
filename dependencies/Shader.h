//
// Created on 2024/9/15.
//

#ifndef RENDERER_SHADER_H
#define RENDERER_SHADER_H

#include "Color.h"
#include "Vertex.h"

template <class T>
class FragmentShader {
    Color apply(Vertex<T>* vertices, const Color& color_interpolated);

    explicit FragmentShader(Color (* prog)(Vertex<T>* vertices, const Color& color_interpolated));

protected:
    Color (* prog)(Vertex<T>* vertices, const Color* color_interpolated);
};

template <class T>
Color FragmentShader<T>::apply(Vertex<T>* vertices, const Color& color_interpolated) {
    return this->prog(vertices, color_interpolated);
}

template <class T>
FragmentShader<T>::FragmentShader(Color (* prog)(Vertex<T>*, const Color&)) {
    this->prog = prog;
}


#endif //RENDERER_SHADER_H
