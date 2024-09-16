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
    void append_triangle(const Triangle<T>& triangle);

    void render_mesh(FrameBuffer* frame_buffer, ZBuffer<T>* z_buffer);

    explicit Mesh(FragmentShader<T> s);

protected:
    std::vector<Triangle<T>> triangles;
    FragmentShader<T> shader;
};

template <class T>
void Mesh<T>::render_mesh(FrameBuffer* frame_buffer, ZBuffer<T>* z_buffer) {
    for (Triangle<T> tri: triangles) {
        Envelope<T> envelope = tri.calculate_envelope(frame_buffer->width - 1, frame_buffer->height - 1);
        for (unsigned int i = envelope.min_x; i <= envelope.max_x; i++) {
            for (unsigned int j = envelope.min_y; j < envelope.max_y; j++) {
                if (tri.contains(i, j)) {
                    if (z_buffer->set_check(i, j, tri.interpolate_depth(i, j))) {
                        auto [alpha, beta, gamma] = tri.calculate_barycentric_2d(i, j);
                        Color c_interpolated = tri.get_vert_color(0)->copy() * alpha + tri.get_vert_color(1)->copy() * beta +
                                               tri.get_vert_color(2)->copy() * gamma;
                        frame_buffer->set_unsafe(i, j, c_interpolated);
                    }
                }
            }
        }
    }
}

template <class T>
void Mesh<T>::append_triangle(const Triangle<T>& triangle) {
    this->triangles.push_back(triangle);
}

template <class T>
Mesh<T>::Mesh(FragmentShader<T> s) {
    this->shader = s;
}


#endif //RENDERER_MESH_H
