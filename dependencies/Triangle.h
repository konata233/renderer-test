//
// Created on 2024/9/15.
//

#ifndef RENDERER_TRIANGLE_H
#define RENDERER_TRIANGLE_H

#include "Vector.h"
#include "Vertex.h"
#include <cmath>

template <class T>
T min4(T a, T b, T c, T d) {
    return std::min(std::min(a, b), std::min(c, d));
}

template <class T>
T max4(T a, T b, T c, T d) {
    return std::max(std::max(a, b), std::max(c, d));
}

template <class T>
struct Envelope {
    T min_x;
    T min_y;
    T max_x;
    T max_y;
};

template <class T>
class Triangle {
public:
    Vertex<T>* vertices;

    bool contains(T x, T y);

    T interpolate_depth(T x, T y);

    const Color* get_vert_color(unsigned int idx);

    Envelope<T> calculate_envelope(T max_x, T max_y);

    auto calculate_barycentric_2d(T x, T y);

    static auto
    calculate_barycentric_2d(T x, T y, const Vector3<T>& vec0, const Vector3<T>& vec1, const Vector3<T>& vec2);

    explicit Triangle(Vertex<T>* vertices);

protected:

    Vector3<T> vec0_2d;
    Vector3<T> vec1_2d;
    Vector3<T> vec2_2d;

    Vector3<T> vec0_3d;
    Vector3<T> vec1_3d;
    Vector3<T> vec2_3d;
};

template <class T>
const Color* Triangle<T>::get_vert_color(unsigned int idx) {
    if (idx >= 3) idx = 2;
    Vertex<T>* vert = &this->vertices[0];
    return vert->get_color();
}

template <class T>
Envelope<T> Triangle<T>::calculate_envelope(T max_x, T max_y) {
    Envelope<T> envelope;
    envelope.min_x = min4(vec0_2d.x, vec1_2d.x, vec2_2d.x, static_cast<T>(max_x)); // !!
    envelope.min_y = min4(vec0_2d.y, vec1_2d.y, vec2_2d.y,  static_cast<T>(max_y));
    envelope.max_x = min4(vec0_2d.x, vec1_2d.x, vec2_2d.x, static_cast<T>(0));
    envelope.max_y = min4(vec0_2d.y, vec1_2d.y, vec2_2d.y, static_cast<T>(0));
    return envelope;
}

template <class T>
auto Triangle<T>::calculate_barycentric_2d(T x, T y) {
    T beta = ((vec0_2d.y - vec2_2d.y) * x + (vec2_2d.x - vec0_2d.x) * y + vec0_2d.x * vec2_2d.x -
              vec2_2d.x * vec0_2d.y) /
             ((vec0_2d.y - vec2_2d.y) * vec1_2d.x + (vec2_2d.x - vec0_2d.x) * vec1_2d.y + vec0_2d.x * vec2_2d.x -
              vec2_2d.x * vec0_2d.y);

    T gamma = ((vec0_2d.y - vec1_2d.y) * x + (vec1_2d.x - vec0_2d.x) * y + vec0_2d.x * vec1_2d.x -
               vec1_2d.x * vec0_2d.y) /
              ((vec0_2d.y - vec1_2d.y) * vec2_2d.x + (vec1_2d.x - vec0_2d.x) * vec2_2d.y + vec0_2d.x * vec1_2d.x -
               vec1_2d.x * vec0_2d.y);

    T alpha = 1 - beta - gamma;

    return std::tuple(alpha, beta, gamma);
}

template <class T>
auto Triangle<T>::calculate_barycentric_2d(T x, T y, const Vector3<T>& vec0, const Vector3<T>& vec1,
                                           const Vector3<T>& vec2) {
    T beta = ((vec0.y - vec2.y) * x + (vec2.x - vec0.x) * y + vec0.x * vec2.x - vec2.x * vec0.y) /
             ((vec0.y - vec2.y) * vec1.x + (vec2.x - vec0.x) * vec1.y + vec0.x * vec2.x - vec2.x * vec0.y);

    T gamma = ((vec0.y - vec1.y) * x + (vec1.x - vec0.x) * y + vec0.x * vec1.x - vec1.x * vec0.y) /
              ((vec0.y - vec1.y) * vec2.x + (vec1.x - vec0.x) * vec2.y + vec0.x * vec1.x - vec1.x * vec0.y);

    T alpha = 1 - beta - gamma;
    return std::tuple(alpha, beta, gamma);
}

template <class T>
bool Triangle<T>::contains(T x, T y) {
    auto p = vec3t(x, y, 0);
    auto ab = vec1_2d - vec0_2d;
    auto bc = vec2_2d - vec1_2d;
    auto ca = vec0_2d - vec2_2d;
    auto ap = p - vec0_2d;
    auto bp = p - vec1_2d;
    auto cp = p - vec2_2d;

    Vector3<T> prod0 = ab ^ ap;
    Vector3<T> prod1 = bc ^ bp;
    Vector3<T> prod2 = ca ^ cp;

    return ((prod0.z >= 0 && prod1.z >= 0 && prod2.z >= 0) ||
            (prod0.z < 0 && prod1.z < 0 && prod2.z < 0));
}

template <class T>
T Triangle<T>::interpolate_depth(T x, T y) {
    T beta = ((vec0_2d.y - vec2_2d.y) * x + (vec2_2d.x - vec0_2d.x) * y + vec0_2d.x * vec2_2d.x -
              vec2_2d.x * vec0_2d.y) /
             ((vec0_2d.y - vec2_2d.y) * vec1_2d.x + (vec2_2d.x - vec0_2d.x) * vec1_2d.y + vec0_2d.x * vec2_2d.x -
              vec2_2d.x * vec0_2d.y);

    T gamma = ((vec0_2d.y - vec1_2d.y) * x + (vec1_2d.x - vec0_2d.x) * y + vec0_2d.x * vec1_2d.x -
               vec1_2d.x * vec0_2d.y) /
              ((vec0_2d.y - vec1_2d.y) * vec2_2d.x + (vec1_2d.x - vec0_2d.x) * vec2_2d.y + vec0_2d.x * vec1_2d.x -
               vec1_2d.x * vec0_2d.y);

    T alpha = 1 - beta - gamma;

    T za = vec0_3d.z;
    T zb = vec1_3d.z;
    T zc = vec2_3d.z;

    T depth = 1 / (alpha / za + beta / zb + gamma / zc);
    return depth;
}

/// Must calculate all the transform of the vertices before initializing triangle!
/// \tparam T
/// \param vertices
template <class T>
Triangle<T>::Triangle(Vertex<T>* vertices) {
    this->vertices = vertices;

    auto t0 = &this->vertices[0].final;
    this->vec0_2d = vec3t(t0->x, t0->y, 0);

    auto t1 = &this->vertices[1].final;
    this->vec1_2d = vec3t(t1->x, t1->y, 0);

    auto t2 = &this->vertices[2].final;
    this->vec2_2d = vec3t(t2->x, t2->y, 0);

    t0 = &this->vertices[0].primary;
    this->vec0_3d = vec3t(t0->x, t0->y, t0->z);

    t1 = &this->vertices[1].primary;
    this->vec1_3d = vec3t(t1->x, t1->y, t1->z);

    t2 = &this->vertices[2].primary;
    this->vec2_3d = vec3t(t2->x, t2->y, t2->z);
}


#endif //RENDERER_TRIANGLE_H
