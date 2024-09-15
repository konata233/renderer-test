//
// Created on 2024/9/14.
//

#ifndef RENDERER_TRANSFORM_MACRO
#define RENDERER_TRANSFORM_MACRO

#define RAD(_deg) (_deg * M_PI / 180.0)
#define SET_COL3(_mat, _col, _vec) \
_mat.set_unsafe(0, _col, _vec.x);  \
_mat.set_unsafe(1, _col, _vec.y);  \
_mat.set_unsafe(2, _col, _vec.z);  \
_mat.set_unsafe(3, _col, 0);

#endif

#ifndef RENDERER_TRANSFORM_H
#define RENDERER_TRANSFORM_H

#include <cmath>
#include "Matrix.h"

template <class T>
class Transform {
public:
    Matrix<T> scale(T sx, T sy, T sz);

    Matrix<T> translate(T tx, T ty, T tz);

    Matrix<T> translate(const Vector3<T>& t_vec);

    Matrix<T> rotate(T rad_x, T rad_y, T rad_z);

    Matrix<T> view(const Vector3<T>& pos, const Vector3<T>& look_at, const Vector3<T>& up);

    Matrix<T> orthographic(T l, T r, T b, T t, T f, T n);

    Matrix<T> frustum(T l, T r, T d, T u, T f, T n);

    Transform();

    ~Transform() = default;
};

// not tested
template <class T>
Matrix<T> Transform<T>::frustum(T l, T r, T d, T u, T f, T n) {
    T data[4][4] {
        {2 * n / (r - l), 0, (r + l) / (r - l), 0},
        {0, 2 * n / (u - d), (u + d) / (u - d), 0},
        {0, 0, (-(f + n)) / (f - n), (-2 * f * n) / (f - n)},
        {0, 0, -1, 0}
    };
    return Matrix<T>(4, 4, data[0]);
}

// not tested
template <class T>
Matrix<T> Transform<T>::orthographic(T l, T r, T b, T t, T f, T n) {
    Matrix<T> translate = this->translate(-(r + l) * 0.5, -(b + t) * 0.5, -(f + n) * 0.5);
    Matrix<T> scale = this->scale(2.0 / (r - l), 2.0 / (t - b), 2.0 / (n - f));

    return scale * translate;
}

template <class T>
Matrix<T> Transform<T>::translate(const Vector3<T>& t_vec) {
    return this->translate(t_vec.x, t_vec.y, t_vec.z);
}

template <class T>
Matrix<T> Transform<T>::view(const Vector3<T>& pos, const Vector3<T>& look_at, const Vector3<T>& up) {
    Matrix<T> t_view = translate(-pos);
    Vector3<T> gt = cross_prod(look_at, up);
    Matrix<T> r_view_inv = Matrix<T>::identity(4);
    SET_COL3(r_view_inv, 0, gt)
    SET_COL3(r_view_inv, 1, up)
    SET_COL3(r_view_inv, 2, -look_at)
    Matrix<T> r_view = r_view_inv.invert();

    return r_view * t_view;
}

template <class T>
Transform<T>::Transform() = default;

template <class T>
Matrix<T> Transform<T>::rotate(T rad_x, T rad_y, T rad_z) {
    Matrix<T> mat_x = Matrix<T>::identity(4);
    Matrix<T> mat_y = mat_x.copy();
    Matrix<T> mat_z = mat_y.copy();

    mat_x.set_unsafe(1, 1, cos(rad_x));
    mat_x.set_unsafe(1, 2, -sin(rad_x));
    mat_x.set_unsafe(2, 1, sin(rad_x));
    mat_x.set_unsafe(2, 2, cos(rad_x));

    mat_y.set_unsafe(0, 0, cos(rad_y));
    mat_y.set_unsafe(0, 2, sin(rad_y));
    mat_y.set_unsafe(2, 0, -sin(rad_y));
    mat_y.set_unsafe(2, 2, cos(rad_y));

    mat_z.set_unsafe(0, 0, cos(rad_z));
    mat_z.set_unsafe(0, 1, -sin(rad_z));
    mat_z.set_unsafe(1, 0, sin(rad_z));
    mat_z.set_unsafe(1, 1, cos(rad_z));

    return mat_x * mat_y * mat_z;
}

template <class T>
Matrix<T> Transform<T>::translate(T tx, T ty, T tz) {
    Matrix<T> mat = Matrix<T>::identity(4);
    mat.set_unsafe(0, 3, tx);
    mat.set_unsafe(1, 3, ty);
    mat.set_unsafe(2, 3, tz);
    return mat;
}

template <class T>
Matrix<T> Transform<T>::scale(T sx, T sy, T sz) {
    T data[4][4] {
        {sx, 0,  0,  0},
        {0,  sy, 0,  0},
        {0,  0,  sz, 0},
        {0,  0,  0,  1}
    };
    return Matrix<T>(4, 4, data[0]);
}

#endif //RENDERER_TRANSFORM_H
