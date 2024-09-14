//
// Created on 2024/9/12.
//

#ifndef RENDERER_MATRIX_H
#define RENDERER_MATRIX_H


#include <cwchar>
#include <sstream>
#include <iostream>
#include "Common.h"
#include "Vector.h"

template <class T>
class Matrix : public Stringify, public PrettyPrint {
public:
    unsigned int row;
    unsigned int col;
    unsigned long size;

    Matrix<T> operator+(T rhs);

    Matrix<T> operator*(T rhs);

    Matrix<T> operator+(Matrix<T>& rhs);

    Matrix<T> operator*(Matrix<T>& rhs);

    Matrix<T> operator*(const Vector3<T>& rhs);

    Matrix<T> operator*(const Vector4<T>& rhs);

    Matrix<T> direct_sum(Matrix<T>& rhs);

    Matrix<T> reshape(unsigned int row_new, unsigned int col_new);

    Matrix<T> augment(unsigned int row_new, unsigned int col_new);

    Matrix<T> invert(bool& error);

    Matrix<T> eliminate(bool& error);

    Matrix<T> eliminate_rev(bool& error);

    Matrix<T> pow(unsigned int n);

    Matrix<T> transpose();

    static Matrix<T> zeros(unsigned int row_init, unsigned int col_init);

    static Matrix<T> identity(unsigned int row_init);

    static Matrix<T> mat3(T data[3]);

    static Matrix<T> mat3(T x, T y, T z);

    static Matrix<T> mat4(T data[4]);

    static Matrix<T> mat4(T x, T y, T z, T w);

    static Matrix<T> from_vec3(const Vector3<T>& vec3);

    static Matrix<T> from_vec4(const Vector4<T>& vec4);

    Matrix<T> copy();

    T at_unsafe(unsigned int row_at, unsigned int col_at);

    T at(unsigned int row_at, unsigned int col_at, bool& error);

    void set_unsafe(unsigned int row_at, unsigned int col_at, T val);

    void set(unsigned int row_at, unsigned int col_at, T val, bool& error);

    std::string stringify() override;

    std::string pretty_print() override;

    Matrix();

    Matrix(unsigned int row_init, unsigned int col_init, const T* data_init);

    ~Matrix();

protected:
    T* data;
};

template <class T>
Matrix<T> Matrix<T>::mat4(T x, T y, T z, T w) {
    T data[4][1]{
        x, y, z, w
    };
    return Matrix<T>::mat4(data[0]);
}

template <class T>
Matrix<T> Matrix<T>::mat3(T x, T y, T z) {
    T data[3][1]{
        x, y, z
    };
    return Matrix<T>::mat3(data[0]);
}

template <class T>
Matrix<T> Matrix<T>::eliminate_rev(bool& error) {
    Matrix<T> eliminated = this->copy();
    for (long i = eliminated.row - 1; i >= 0; i--) {
        T first_pivot = eliminated.at_unsafe(i, i);
        if (first_pivot == 0) {
            if (i - 1 >= 0) {
                T replace = eliminated.at_unsafe(i - 1, i);
                if (replace == 0) {
                    error = true;
                    return Matrix();
                } else {
                    eliminated.set_unsafe(i - 1, i, 0);
                    eliminated.set_unsafe(i, i, replace);
                }
            } else {
                error = true;
                return Matrix();
            }
        }
        for (long j = i - 1; j >= 0; j--) {
            T first_elem = eliminated.at_unsafe(j, i);
            long double mul = first_elem / first_pivot;

            eliminated.set_unsafe(j, i, 0);
            for (long k = eliminated.col - 1; k > j + 1; k--) {
                eliminated.set_unsafe(j, k, eliminated.at_unsafe(j, k) - eliminated.at_unsafe(i, k) * mul);
            }
        }
    }
    return eliminated;
}

template <class T>
Matrix<T> Matrix<T>::eliminate(bool& error) {
    Matrix<T> eliminated = this->copy();
    for (unsigned int i = 0; i < eliminated.row - 1; i++) {
        T first_pivot = eliminated.at_unsafe(i, i);
        if (first_pivot == 0) {
            if (i + 1 < eliminated.row) {
                T replace = eliminated.at_unsafe(i + 1, i);
                if (replace == 0) {
                    error = true;
                    return Matrix();
                } else {
                    eliminated.set_unsafe(i + 1, i, 0);
                    eliminated.set_unsafe(i, i, replace);
                }
            } else {
                error = true;
                return Matrix();
            }
        }
        for (unsigned int j = i + 1; j < eliminated.row; j++) {
            T first_elem = eliminated.at_unsafe(j, i);
            long double mul = first_elem / first_pivot;

            eliminated.set_unsafe(j, i, 0);
            for (unsigned int k = j; k < eliminated.col; k++) {
                eliminated.set_unsafe(j, k, eliminated.at_unsafe(j, k) - eliminated.at_unsafe(i, k) * mul);
            }
        }
    }
    return eliminated;
}

template <class T>
Matrix<T> Matrix<T>::invert(bool& error) {
    unsigned int r = this->row;
    unsigned int c = this->col;
    if (r != c) {
        error = true;
        return Matrix();
    }

    Matrix<T> augmented = this->augment(r, c * 2);
    Matrix<T> id = Matrix::identity(r);
    for (unsigned int i = 0; i < r; i++) {
        for (unsigned int j = 0; j < c; j++) {
            augmented.set_unsafe(i, j + c, id.at_unsafe(i, j));
        }
    }

    if (error) {
        return Matrix();
    }

    augmented = augmented.eliminate(error).eliminate_rev(error);

    for (unsigned int i = 0; i < augmented.row; i++) {
        T mul = 1 / augmented.at_unsafe(i, i);
        for (unsigned int j = 0; j < augmented.col; j++) {
            augmented.set_unsafe(i, j, augmented.at_unsafe(i, j) * mul);
        }
    }

    Matrix<T> inverted = Matrix::zeros(r, c);
    for (unsigned int i = 0; i < r; i++) {
        for (unsigned int j = 0; j < c; j++) {
            inverted.set_unsafe(i, j, augmented.at_unsafe(i, j + c));
        }
    }
    return inverted;
}

template <class T>
Matrix<T> Matrix<T>::pow(unsigned int n) {
    Matrix init = this->copy();
    Matrix mat = this->copy();
    for (unsigned int i = 0; i < n - 1; i++) {
        mat = mat * init;
    }
    return mat;
}

template <class T>
Matrix<T> Matrix<T>::augment(unsigned int row_new, unsigned int col_new) {
    row_new = row_new > this->row ? row_new : this->row;
    col_new = col_new > this->col ? col_new : this->col;
    Matrix<T> mat = Matrix::zeros(row_new, col_new);
    for (unsigned int i = 0; i < this->row; i++) {
        for (unsigned int j = 0; j < this->col; j++) {
            mat.set_unsafe(i, j, this->at_unsafe(i, j));
        }
    }
    return mat;
}

template <class T>
Matrix<T> Matrix<T>::identity(unsigned int row_init) {
    Matrix<T> mat = Matrix::zeros(row_init, row_init);
    for (unsigned int i = 0; i < row_init; i++) {
        mat.set_unsafe(i, i, 1);
    }
    return mat;
}

template <class T>
Matrix<T> Matrix<T>::from_vec4(const Vector4<T>& vec4) {
    T data[4][1]{
            vec4.x, vec4.y, vec4.z, vec4.w
    };

    Matrix<T> mat = Matrix(4, 1, data[0]);
    return mat;
}

template <class T>
Matrix<T> Matrix<T>::from_vec3(const Vector3<T>& vec3) {
    T data[3][1]{
            vec3.x, vec3.y, vec3.z
    };

    Matrix<T> mat = Matrix<T>(3, 1, data[0]);
    return mat;
}

template <class T>
Matrix<T> Matrix<T>::mat4(T* data) {
    Matrix<T> mat = Matrix<T>(4, 1, data);
    return mat;
}

template <class T>
Matrix<T> Matrix<T>::mat3(T* data) {
    Matrix<T> mat = Matrix<T>(3, 1, data);
    return mat;
}

template <class T>
std::string Matrix<T>::pretty_print() {
    std::stringstream ss;
    ss << "[";
    for (unsigned int i = 0; i < this->row; i++) {
        ss << "[";
        for (unsigned int j = 0; j < this->col; j++) {
            j != this->col - 1 ? ss << this->at_unsafe(i, j) << ", " : ss << this->at_unsafe(i, j);
        }
        i != this->row - 1 ? ss << "]," << std::endl : ss << "]";
    }
    ss << "]";
    return ss.str();
}

/// Overwritten operator * for matrix multiplication. Note that the matrices must satisfy mat1(MxN) and mat2(NxP)!!
/// \tparam T Data type.
/// \param rhs Right-hand operand.
/// \return Result of the multiplication.
template <class T>
Matrix<T> Matrix<T>::operator*(Matrix<T>& rhs) {
    Matrix<T> mat = Matrix<T>::zeros(this->row, rhs.col);
    for (unsigned int i = 0; i < this->row; i++) {
        for (unsigned int j = 0; j < rhs.col; j++) {
            for (unsigned int k = 0; k < this->col; k++) {
                T prev = mat.at_unsafe(i, j);
                mat.set_unsafe(i, j, this->at_unsafe(i, k) * rhs.at_unsafe(k, j) + prev);
            }
        }
    }
    return mat;
}

template <class T>
std::string Matrix<T>::stringify() {
    std::stringstream ss;
    ss << "[";
    for (unsigned int i = 0; i < this->row; i++) {
        ss << "[";
        for (unsigned int j = 0; j < this->col; j++) {
            j != this->col - 1 ? ss << this->at_unsafe(i, j) << ", " : ss << this->at_unsafe(i, j);
        }
        i != this->row - 1 ? ss << "], " : ss << "]";
    }
    ss << "]";
    return ss.str();
}

template <class T>
Matrix<T> Matrix<T>::operator*(const Vector4<T>& rhs_v) {
    Matrix<T> rhs = Matrix::from_vec4(rhs_v);
    Matrix<T> mat = Matrix<T>::zeros(this->row, rhs.col);
    for (unsigned int i = 0; i < this->row; i++) {
        for (unsigned int j = 0; j < rhs.col; j++) {
            for (unsigned int k = 0; k < this->col; k++) {
                T prev = mat.at_unsafe(i, j);
                mat.set_unsafe(i, j, this->at_unsafe(i, k) * rhs.at_unsafe(k, j) + prev);
            }
        }
    }
    return mat;
}

template <class T>
Matrix<T> Matrix<T>::operator*(const Vector3<T>& rhs_v) {
    Matrix<T> rhs = Matrix::from_vec3(rhs_v);
    Matrix<T> mat = Matrix<T>::zeros(this->row, rhs.col);
    for (unsigned int i = 0; i < this->row; i++) {
        for (unsigned int j = 0; j < rhs.col; j++) {
            for (unsigned int k = 0; k < this->col; k++) {
                T prev = mat.at_unsafe(i, j);
                mat.set_unsafe(i, j, this->at_unsafe(i, k) * rhs.at_unsafe(k, j) + prev);
            }
        }
    }
    return mat;
}


template <class T>
Matrix<T> Matrix<T>::transpose() {
    Matrix<T> transposed = Matrix<T>::zeros(this->col, this->row);
    for (unsigned int i = 0; i < transposed.row; i++) {
        for (unsigned int j = 0; j < transposed.col; j++) {
            transposed.set_unsafe(i, j, this->at_unsafe(j, i));
        }
    }
    return transposed;
}

/// Reshapes the original matrix m×n to p×q (m×n == p×q).
/// \tparam T Data type of the matrix.
/// \param row_new p
/// \param col_new q
/// \return New matrix p×q. (original matrix if m×n != p×q!!)
template <class T>
Matrix<T> Matrix<T>::reshape(unsigned int row_new, unsigned int col_new) {
    if (row_new * col_new != this->size) {
        return *this;
    } else {
        auto* mat = new Matrix<T>(row_new, col_new, this->data);
        return *mat;
    }
}

template <class T>
Matrix<T> Matrix<T>::direct_sum(Matrix<T>& rhs) {
    unsigned int new_row = this->row + rhs.row;
    unsigned int new_col = this->col + rhs.col;

    unsigned int offset_r = this->row;
    unsigned int offset_c = this->col;

    Matrix<T> mat = Matrix::zeros(new_row, new_col);
    for (unsigned int i = 0; i < this->row; i++) {
        for (unsigned int j = 0; j < this->col; j++) {
            mat.set_unsafe(i, j, this->at_unsafe(i, j));
        }
    }
    for (unsigned int i = this->row; i < new_row; i++) {
        for (int j = this->col; j < new_col; j++) {
            mat.set_unsafe(i, j, rhs.at_unsafe(i - offset_r, j - offset_c));
        }
    }
    return mat;
}

/// Overwritten operator + of Matrix.
/// \tparam T Data type of the matrix.
/// \param rhs Right-hand operand.
/// \return the sum of two matrices. **(Left-hand operand if number of the rows or columns are not strictly equivalent!!)**
template <class T>
Matrix<T> Matrix<T>::operator+(Matrix<T>& rhs) {
    if (rhs.row != this->row || rhs.col != this->col) {
        return *this;
    } else {
        Matrix<T> mat = this->copy();
        for (unsigned int i = 0; i < mat->row; i++) {
            for (unsigned int j = 0; j < mat->col; j++) {
                mat.set_unsafe(i, j, rhs.at_unsafe(i, j));
            }
        }
        return mat;
    }
}

template <class T>
Matrix<T> Matrix<T>::operator*(T rhs) {
    Matrix<T> mat = this->copy();
    for (unsigned int i = 0; i < this->row; i++) {
        for (unsigned int j = 0; j < this->col; j++) {
            mat.set_unsafe(i, j, this->at_unsafe(i, j) * rhs);
        }
    }
    return mat;
}

template <class T>
void Matrix<T>::set(unsigned int row_at, unsigned int col_at, T val, bool& error) {
    if (row_at >= this->row || col_at >= this->col) {
        error = true;
        return;
    } else {
        error = false;
        this->data[row_at * this->col + col_at] = val;
    }
}

template <class T>
void Matrix<T>::set_unsafe(unsigned int row_at, unsigned int col_at, T val) {
    this->data[row_at * this->col + col_at] = val;
}

template <class T>
Matrix<T> Matrix<T>::copy() {
    auto mat = Matrix<T>(this->row, this->col, this->data);
    return mat;
}

template <class T>
Matrix<T> Matrix<T>::operator+(T rhs) {
    if (rhs == NULL) {
        rhs = 0;
    }
    Matrix<double> mat = this->copy();
    for (unsigned int i = 0; i < this->row; i++) {
        for (unsigned int j = 0; j < this->col; j++) {
            mat.set_unsafe(i, j, this->at_unsafe(i, j) + rhs);
        }
    }
    return mat;
}

/// Get the value of designated position in the matrix (unsafe).
/// Note that though this method may have potential risk of undefined op,
/// it can be faster than Matrix<T>::at(), see also: NRVO mechanism of cpp 11.
/// \tparam T
/// \param row_at
/// \param col_at
/// \return
template <class T>
T Matrix<T>::at_unsafe(unsigned int row_at, unsigned int col_at) {
    return this->data[row_at * this->col + col_at];
}

template <class T>
T Matrix<T>::at(unsigned int row_at, unsigned int col_at, bool& error) {
    if (row_at >= this->row || col_at >= this->col) {
        error = true;
        return NULL;
    } else {
        error = false;
        return this->data[row_at * this->col + col_at];
    }
}

template <class T>
Matrix<T>::Matrix() {
    this->row = 0;
    this->col = 0;
    this->size = 0;
    this->data = nullptr;
}

template <class T>
Matrix<T>::Matrix(unsigned int row_init, unsigned int col_init, const T* data_init) {
    this->row = row_init;
    this->col = col_init;
    this->size = row_init * col_init;

    this->data = new T[this->size];
    T* ptr = this->data;
    for (unsigned int i = 0; i < this->size; i++) {
        *ptr = data_init[i];
        ptr++;
    }
}

template <class T>
Matrix<T> Matrix<T>::zeros(unsigned int row_init, unsigned int col_init) {
    auto mat = Matrix<T>();
    mat.row = row_init;
    mat.col = col_init;
    mat.size = row_init * col_init;

    mat.data = new T[mat.size];
    T* ptr = mat.data;
    for (unsigned int i = 0; i < mat.size; i++) {
        *ptr = 0;
        ptr++;
    }
    return mat;
}

template <class T>
Matrix<T>::~Matrix() {

}

#endif //RENDERER_MATRIX_H

#ifndef RENDERER_MATRIX_MACRO
#define RENDERER_MATRIX_MACRO

#define mi  Matrix<int>
#define mf  Matrix<float>
#define md  Vector3<double>
#define mld Vector3<long double>

#define mat4f(_x, _y, _z, _w)  Matrix<float>::mat4(_x, _y, _z, _w)
#define mat4d(_x, _y, _z, _w)  Matrix<double>::mat4(_x, _y, _z, _w)
#define mat4ld(_x, _y, _z, _w) Matrix<long double>::mat4(_x, _y, _z, _w)

#endif //RENDERER_MATRIX_MACRO
