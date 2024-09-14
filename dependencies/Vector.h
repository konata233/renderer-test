//
// Created on 2024/9/12.
//

#ifndef RENDERER_VECTOR_H
#define RENDERER_VECTOR_H

#include "Common.h"

template <class T>
class Vector : public Stringify {
/*
    friend T dot_prod(const Vector<T>& lhs, const Vector<T>& rhs);
    friend Vector<T> cross_prod(const Vector<T>& lhs, const Vector<T>& rhs);
*/
public:
    virtual Vector<T> operator+() = 0;

    virtual Vector<T> operator+(const Vector<T>& rhs) = 0;

    virtual Vector<T> operator-() = 0;

    virtual Vector<T> operator-(const Vector<T>& rhs) = 0;

    virtual Vector<T> operator*(T rhs) = 0;

    virtual Vector<T> copy() = 0;

    virtual T dot_prod(const Vector<T>& rhs) = 0;

    virtual Vector<T> cross_prod(const Vector<T>& rhs) = 0;

    virtual T mod() = 0;

    virtual Vector<T> normalize() = 0;

    std::string stringify() override = 0;
};

template <class T>
class Vector3 : public Stringify {
    friend T dot_prod(const Vector3<T>& lhs, const Vector3<T>& rhs);

    friend Vector3<T> cross_prod(const Vector3<T>& lhs, const Vector3<T>& rhs);

    friend T mod(const Vector3& op);

    friend Vector3<T> normalize(const Vector3& op);

    friend Vector3<T> const_copy(const Vector3<T>& op);

public:
    T x;
    T y;
    T z;

    Vector3<T> operator+();

    Vector3<T> operator+(const Vector3<T>& rhs);

    Vector3<T> operator-();

    Vector3<T> operator-(const Vector3<T>& rhs);

    Vector3<T> operator*(T rhs);

    Vector3<T> operator^(const Vector3<T>& rhs);

    Vector3<T> copy();

    T dot_prod(const Vector3<T>& rhs);

    Vector3<T> cross_prod(const Vector3<T>& rhs);

    T mod();

    Vector3<T> normalize();

    std::string stringify() override;

    Vector3();

    Vector3(T x, T y, T z);

    ~Vector3();
};

template <class T>
Vector3<T> Vector3<T>::operator^(const Vector3<T>& rhs) {
    return this->cross_prod(rhs);
}

template <class T>
class Vector4 : public Stringify {
    friend T dot_prod(const Vector4<T>& lhs, const Vector4<T>& rhs);

    friend Vector4<T> cross_prod(const Vector4<T>& lhs, const Vector4<T>& rhs);

    friend T mod(const Vector4<T>& op);

    friend Vector4<T> normalize(const Vector4<T>& op);

public:
    T x;
    T y;
    T z;
    T w;

    Vector4<T> operator+();

    Vector4<T> operator+(const Vector4<T>& rhs);

    Vector4<T> operator-();

    Vector4<T> operator-(const Vector4<T>& rhs);

    Vector4<T> operator*(T rhs);

    Vector4<T> copy();

    T dot_prod(const Vector4<T>& rhs);

    Vector4<T> cross_prod(const Vector4<T>& rhs);

    T mod();

    Vector4<T> normalize();

    std::string stringify() override;

    Vector4();

    Vector4(T x, T y, T z, T w);

    ~Vector4();
};

#include <cmath>
#include <sstream>

// implementation for vector3
template <class T>
Vector3<T> Vector3<T>::operator-(const Vector3<T>& rhs) {
    auto v3 = Vector3();
    v3.x = this->x - rhs.x;
    v3.y = this->y - rhs.y;
    v3.z = this->z - rhs.z;
    return v3;
}

template <class T>
Vector3<T> Vector3<T>::operator-() {
    auto v3 = Vector3();
    v3.x = -this->x;
    v3.y = -this->y;
    v3.z = -this->z;
    return v3;
}

template <class T>
Vector3<T> Vector3<T>::operator+(const Vector3<T>& rhs) {
    auto v3 = Vector3();
    v3.x = this->x + rhs.x;
    v3.y = this->y + rhs.y;
    v3.z = this->z + rhs.z;
    return v3;
}

template <class T>
Vector3<T> Vector3<T>::copy() {
    auto v3 = Vector3<T>();
    v3.x = static_cast<T>(this->x);
    v3.y = static_cast<T>(this->y);
    v3.z = static_cast<T>(this->z);
    return v3;
}

template <class T>
Vector3<T> const_copy(const Vector3<T>& op) {
    auto v3 = Vector3<T>();
    v3.x = static_cast<T>(op.x);
    v3.y = static_cast<T>(op.y);
    v3.z = static_cast<T>(op.z);
    return v3;
}

template <class T>
Vector3<T>::~Vector3() = default;

template <class T>
Vector3<T>::Vector3(T x, T y, T z) {
    this->x = static_cast<T>(x);
    this->y = static_cast<T>(y);
    this->z = static_cast<T>(z);
}

template <class T>
Vector3<T>::Vector3() {
    this->x = static_cast<T>(0);
    this->y = static_cast<T>(0);
    this->z = static_cast<T>(0);
}

template <class T>
Vector3<T> Vector3<T>::operator+() {
    return this->copy();
}


template <class T>
Vector3<T> Vector3<T>::normalize() {
    T mul = 1 / mod(*this);
    auto v3 = Vector3<T>();
    v3.x = this->x * mul;
    v3.y = this->y * mul;
    v3.z = this->z * mul;
    return v3;
}

template <class T>
T Vector3<T>::mod() {
    return static_cast<T>(
            sqrtl(
                    static_cast<long double>(
                            powl(this->x, 2) +
                            powl(this->y, 2) +
                            powl(this->z, 2)
                    )
            )
    );
}

template <class T>
Vector3<T> Vector3<T>::cross_prod(const Vector3<T>& rhs) {
    auto vec3 = Vector3<T>();
    vec3.x = this->y * rhs.z - this->z * rhs.y;
    vec3.y = this->z * rhs.x - this->x * rhs.z;
    vec3.z = this->x * rhs.y - this->y * rhs.x;
    return vec3;
}

template <class T>
T Vector3<T>::dot_prod(const Vector3<T>& rhs) {
    return static_cast<T>(
            this->x * rhs.x +
            this->y * rhs.y +
            this->z * rhs.z
    );
}

template <class T>
Vector3<T> Vector3<T>::operator*(T rhs) {
    auto v3 = Vector3<T>();
    v3.x = this->x * rhs;
    v3.y = this->y * rhs;
    v3.z = this->z * rhs;
    return v3;
}

template <class T>
Vector3<T> normalize(const Vector3<T>& op) {
    T mul = 1 / mod(op);
    auto v3 = Vector3<T>();
    v3.x = op.x * mul;
    v3.y = op.y * mul;
    v3.z = op.z * mul;
    return v3;
}

template <class T>
T mod(const Vector3<T>& op) {
    return static_cast<T>(
            sqrtl(
                    static_cast<long double>(
                            powl(op.x, 2) +
                            powl(op.y, 2) +
                            powl(op.z, 2)
                    )
            )
    );
}

template <class T>
Vector3<T> cross_prod(const Vector3<T>& lhs, const Vector3<T>& rhs) {
    auto vec3 = Vector3<T>();
    vec3.x = lhs.y * rhs.z - lhs.z * rhs.y;
    vec3.y = lhs.z * rhs.x - lhs.x * rhs.z;
    vec3.z = lhs.x * rhs.y - lhs.y * rhs.x;
    return vec3;
}

template <class T>
T dot_prod(const Vector3<T>& lhs, const Vector3<T>& rhs) {
    return static_cast<T>(
            lhs.x * rhs.x +
            lhs.y * rhs.y +
            lhs.z * rhs.z
    );
}


template <class T>
std::string Vector3<T>::stringify() {
    std::stringstream ss;
    ss << "Vector3(";
    ss << this->x << ", " << this->y << ", " << this->z << ")";
    return ss.str();
}

// implementation for vector4
template <class T>
Vector4<T> Vector4<T>::operator-(const Vector4<T>& rhs) {
    return (*this) + (-rhs);
}

template <class T>
Vector4<T> Vector4<T>::operator-() {
    auto v4 = Vector4();
    v4.x = -this->x;
    v4.y = -this->y;
    v4.z = -this->z;
    v4.w = -this->w;
    return v4;
}

template <class T>
Vector4<T>::Vector4(T x, T y, T z, T w) {
    this->x = static_cast<T>(x);
    this->y = static_cast<T>(y);
    this->z = static_cast<T>(z);
    this->w = static_cast<T>(w);
}

template <class T>
Vector4<T>::~Vector4() = default;

template <class T>
Vector4<T>::Vector4() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->w = 0;
}

template <class T>
Vector4<T> Vector4<T>::operator+(const Vector4<T>& rhs) {
    auto v4 = Vector4();
    v4.x = this->x + rhs.x;
    v4.y = this->y + rhs.y;
    v4.z = this->z + rhs.z;
    v4.w = this->w + rhs.w;
    return v4;
}

template <class T>
Vector4<T> Vector4<T>::copy() {
    auto v4 = Vector4();
    v4.x = this->x;
    v4.y = this->y;
    v4.z = this->z;
    v4.w = this->w;
    return v4;
}

template <class T>
Vector4<T> Vector4<T>::operator+() {
    return this->copy();
}

template <class T>
T Vector4<T>::mod() {
    return static_cast<T>(
            sqrtl(
                    static_cast<long double>(
                            powl(this->x, 2) +
                            powl(this->y, 2) +
                            powl(this->z, 2) +
                            powl(this->w, 2)
                    )
            )
    );
}

template <class T>
T mod(const Vector4<T>& op) {
    return static_cast<T>(
            sqrtl(
                    static_cast<long double>(
                            powl(op.x, 2) +
                            powl(op.y, 2) +
                            powl(op.z, 2) +
                            powl(op.w, 2)
                    )
            )
    );
}

template <class T>
T Vector4<T>::dot_prod(const Vector4<T>& rhs) {
    return static_cast<T>(
            this->x * rhs.x +
            this->y * rhs.y +
            this->z * rhs.z +
            this->w * rhs.w
    );
}

template <class T>
Vector4<T> Vector4<T>::operator*(T rhs) {
    Vector4<T> v4 = Vector4<T>();
    v4.x = this->x * rhs;
    v4.y = this->y * rhs;
    v4.z = this->z * rhs;
    v4.w = this->w * rhs;
    return v4;
}

template <class T>
T dot_prod(const Vector4<T>& lhs, const Vector4<T>& rhs) {
    return static_cast<T>(
            lhs.x * rhs.x +
            lhs.y * rhs.y +
            lhs.z * rhs.z +
            lhs.w * rhs.w
    );
}


template <class T>
Vector4<T> normalize(const Vector4<T>& op) {
    T mul = 1 / mod(op);
    auto v4 = Vector4<T>();
    v4.x = op.x * mul;
    v4.y = op.y * mul;
    v4.z = op.z * mul;
    v4.w = op.w * mul;
    return v4;
}

template <class T>
Vector4<T> Vector4<T>::normalize() {
    T mul = 1 / mod(*this);
    auto v4 = Vector4<T>();
    v4.x = this->x * mul;
    v4.y = this->y * mul;
    v4.z = this->z * mul;
    v4.w = this->w * mul;
    return v4;
}

template <class T>
Vector4<T> Vector4<T>::cross_prod(const Vector4<T>& rhs) {
    // todo
}

template <class T>
Vector4<T> cross_prod(const Vector4<T>& lhs, const Vector4<T>& rhs) {
    // todo
}

template <class T>
std::string Vector4<T>::stringify() {
    std::stringstream ss;
    ss << "Vector4(";
    ss << this->x << ", " << this->y << ", " << this->z << ", " << this->w << ")";
    return ss.str();
}

#endif //RENDERER_VECTOR_H

#ifndef RENDERER_VECTOR_MACRO
#define RENDERER_VECTOR_MACRO

#define v3i  Vector3<int>
#define v3f  Vector3<float>
#define v3d  Vector3<double>
#define v3ld Vector3<long double>

#endif //RENDERER_VECTOR_MACRO
