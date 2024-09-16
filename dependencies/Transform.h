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

#define trans_f  Transform<float>
#define trans_d  Transform<double>
#define trans_ld Transform<long double>

#endif

#ifndef RENDERER_TRANSFORM_H
#define RENDERER_TRANSFORM_H

#include <cmath>
#include "Matrix.h"

template <class T>
class Transform {
public:
    static Matrix<T> scale(T sx, T sy, T sz);

    static Matrix<T> translate(T tx, T ty, T tz);

    static Matrix<T> translate(const Vector3<T>& t_vec);

    static Matrix<T> rotate(T rad_x, T rad_y, T rad_z);

    static Matrix<T> view(const Vector3<T>& pos, const Vector3<T>& look_at, const Vector3<T>& up, bool& error);

    static Matrix<T> orthographic(T left, T right, T bottom, T top, T far, T near);

    static Matrix<T> frustum(T left, T right, T bottom, T top, T far, T near);

    static Matrix<T> frustum(T fov_y, T wh_aspect, T far, T near);

    static Matrix<T> viewport(T viewport_width, T viewport_height);

    Transform();

    ~Transform() = default;
};

template <class T>
Matrix<T> Transform<T>::viewport(T viewport_width, T viewport_height) {
    Matrix<T> mat = Matrix<T>::identity(4);
    mat.set_unsafe(0, 0, viewport_width * -0.5); // necessary reverse to convert x=±0.5 to scr_x=0, 100 respectively.
    mat.set_unsafe(1, 1, viewport_height * 0.5);
    auto v3 = vec3t(viewport_width * 0.5, viewport_height * 0.5, 0);
    SET_COL3(mat, 3, v3);
    return mat;
}

template <class T>
Matrix<T> Transform<T>::frustum(T fov_y, T wh_aspect, T far, T near) {
    T t = std::tan(fov_y / 2) * std::abs(near);
    T b = -t;
    T r = wh_aspect * t;
    T l = -r;
    return frustum(l, r, b, t, far, near);
}

// tested (limited cases)
template <class T>
Matrix<T> Transform<T>::frustum(T left, T right, T bottom, T top, T far, T near) {
    T w = std::abs(right - left);
    T h = std::abs(top - bottom);
    T data[4][4]{
            {2 * near / w, 0,            0,                           0},
            {0,            2 * near / h, 0,                           0},
            {0,            0,            (near + far) / (near - far), (-2 * far * near) / (near - far)},
            {0,            0,            0,                           1}
    };
    return Matrix<T>(4, 4, data[0]);
}

// tested (limited cases)
template <class T>
Matrix<T> Transform<T>::orthographic(T left, T right, T bottom, T top, T far, T near) {
    Matrix<T> t = translate(-(right + left) * 0.5, -(bottom + top) * 0.5, -(far + near) * 0.5);
    Matrix<T> s = scale(2.0 / (right - left), 2.0 / (top - bottom), 2.0 / (near - far));

    return s * t;
}

template <class T>
Matrix<T> Transform<T>::translate(const Vector3<T>& t_vec) {
    return translate(t_vec.x, t_vec.y, t_vec.z);
}

template <class T>
Matrix<T> Transform<T>::view(const Vector3<T>& pos, const Vector3<T>& look_at, const Vector3<T>& up, bool& error) {
    Matrix<T> t_view = translate(-pos.copy());
    Vector3<T> gt = look_at.cross_prod(up);
    Matrix<T> r_view_inv = Matrix<T>::identity(4);
    SET_COL3(r_view_inv, 0, gt)
    SET_COL3(r_view_inv, 1, up)
    SET_COL3(r_view_inv, 2, -look_at)
    Matrix<T> r_view = r_view_inv.invert(error);

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
    T data[4][4]{
            {sx, 0,  0,  0},
            {0,  sy, 0,  0},
            {0,  0,  sz, 0},
            {0,  0,  0,  1}
    };
    return Matrix<T>(4, 4, data[0]);
}

#endif //RENDERER_TRANSFORM_H
