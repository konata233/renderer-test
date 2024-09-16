//
// Created on 2024/9/16.
//

#ifndef RENDERER_MESH_H
#define RENDERER_MESH_H


#include <vector>
#include "Triangle.h"
#include "Shader.h"

template <class T>
class Mesh {
public:
    void append_triangle(Triangle<T> triangle);

    void render_mesh();

    explicit Mesh(FragmentShader<T> s);

protected:
    std::vector<Triangle<T>> triangles;
    FragmentShader<T> shader;
};

template <class T>
Mesh<T>::Mesh(FragmentShader<T> s) {

}


#endif //RENDERER_MESH_H
