//
// Created on 2024/9/16.
//

#ifndef RENDERER_MESH_H
#define RENDERER_MESH_H


#include <vector>
#include "Triangle.h"
#include "Shader.h"
#include "Buffer.h"

template <class T>
class Mesh {
public:
    Mesh<T>* append_triangle(const Triangle<T>& triangle);

    void render_mesh(FrameBuffer* frame_buffer, ZBuffer<T>* z_buffer);

    Mesh<T>* ready();

    Mesh<T>* apply_model_transform(Matrix<T>& transform);

    Mesh<T>* apply_view_persp_transform(Matrix<T>& transform);

    Mesh<T>* apply_viewport_transform(Matrix<T>& viewport);

    explicit Mesh(FragmentShader<T> s);

    std::vector<Triangle<T>> triangles;

    FragmentShader<T> shader;
};

template <class T>
Mesh<T>* Mesh<T>::apply_model_transform(Matrix<T>& transform) {
    for (auto& tri: this->triangles) {
        tri.apply_model_transform(transform);
    }
    return this;
}

template <class T>
Mesh<T>* Mesh<T>::ready() {
    for (auto& tri: this->triangles) {
        tri.ready();
    }
    return this;
}

template <class T>
Mesh<T>* Mesh<T>::apply_viewport_transform(Matrix<T>& viewport) {
    for (auto& tri: this->triangles) {
        tri.apply_viewport_transform(viewport);
    }
    return this;
}

template <class T>
Mesh<T>* Mesh<T>::apply_view_persp_transform(Matrix<T>& transform) {
    for (auto& tri: this->triangles) {
        tri.apply_view_persp_transform(transform);
    }
    return this;
}

template <class T>
void Mesh<T>::render_mesh(FrameBuffer* frame_buffer, ZBuffer<T>* z_buffer) {
    for (Triangle<T>& tri: triangles) {
        Envelope<T> envelope = tri.calculate_envelope(frame_buffer->width - 1, frame_buffer->height - 1);
        for (unsigned int i = envelope.min_x; i <= envelope.max_x; i++) {
            for (unsigned int j = envelope.min_y; j <= envelope.max_y; j++) {
                if (tri.contains(i, j)) {
                    if (z_buffer->set_check(i, j, tri.interpolate_depth(i, j))) {
                        auto [alpha, beta, gamma] = tri.calculate_barycentric_2d(i, j);
                        auto z = tri.interpolate_depth(i, j);
                        auto [za, zb, zc] = tri.depths();
                        Color c_interpolated = (tri.get_vert_color(0)->copy()  * (z * alpha / za) + tri.get_vert_color(1)->copy() * (z * beta / zb) +
                                               tri.get_vert_color(2)->copy() * (z * gamma / zc));
                        frame_buffer->set_unsafe(i, j, this->shader.apply(tri.vertices, c_interpolated));
                    }
                }
            }
        }
    }
}

template <class T>
Mesh<T>* Mesh<T>::append_triangle(const Triangle<T>& triangle) {
    this->triangles.push_back(triangle);
    return this;
}

template <class T>
Mesh<T>::Mesh(FragmentShader<T> s) {
    this->shader = s;
}


#endif //RENDERER_MESH_H
