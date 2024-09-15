#include <iostream>
#include "dependencies/Vector.h"
#include "dependencies/Matrix.h"
#include "dependencies/Transform.h"

int main() {
    //std::cout<<"hello";
    v3d v1(1, 2, 4);
    //std::cout << v1.stringify();
    v3d v2(-5, 4, -3);
    auto sum = v1 + v2;
    //std::cout<<sum.stringify();
    auto sub = v1 - v2;
    auto dot_prod = v1.dot_prod(v2);
    auto cross_prod = v1.cross_prod(v2);
    auto mod1 = v1.mod();
    auto mod2 = v2.mod();
    std::cout << sum.stringify() << sub.stringify() << std::endl;
    std::cout << dot_prod << std::endl << cross_prod.stringify() << std::endl;
    std::cout << mod1 << std::endl;

    double arr[2][3] {
            {0, 3, 2},
            {6, 1, 5},
    };
    double arr2[3][3] {
            {1, 2, 1},
            {3,8, 5},
            {4, 9, 7}
    };
    auto mat = Matrix<double>(2, 3, arr[0]);
    auto mat2 = Matrix<double>(3, 3, arr2[0]);
    auto mul = mat * mat2;
    std::cout << mat.stringify() << std::endl;
    std::cout << mat.transpose().stringify() << std::endl;
    std::cout << mul.pretty_print() << std::endl;
    std::cout << "-----------------------" << std::endl;

    v3d vx(1, 2, 0);
    double arr3[3][3] {
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 1}
    };
    auto mat3 = Matrix<double>(3, 3, arr3[0]);
    std::cout << (mat3 * vx).pretty_print() << std::endl;
    std::cout << "-----------------------" << std::endl;
    double arr4[2][2] {
            {2, 3},
            {4, 5}
    };
    auto mat4 = Matrix<double>(2, 2, arr4[0]);
    std::cout << mat4.pow(3).pretty_print() << std::endl;
    std::cout << "-----------------------" << std::endl;
    double arr5[3][3] {
            {2, -1, 0},
            {-1, 5, -1},
            {0, -1, 4}
    };
    auto mat5 = Matrix<double>(3, 3, arr5[0]);
    bool err;
    std::cout << mat5.invert(err).pretty_print() << std::endl;
    std::cout << "-----------------------" << std::endl;

    auto mat6 = mat4f(1, 2, 3, 1);
    std::cout << mat6.pretty_print() << std::endl;
    std::cout << "-----------------------" << std::endl;

    auto vt = vec4f(0.5, 0.8, 1, 1);
    auto view = trans_f::view(vec3f(0, 0, 0), vec3f(0, 0, 1), vec3f(0, 1, 0), err);
    auto fru = Transform<float>::frustum(RAD(75), 1, 1, 0.1);
    auto ortho = trans_f::orthographic(-1, 1, -1, 1, 1, -1);
    auto viewport = Transform<float>::viewport(100, 100);
    std::cout << "----------00000-------------" << std::endl;
    std::cout << (fru.pretty_print()) << std::endl;
    std::cout << (viewport * ortho * view).pretty_print() << std::endl;
    std::cout << (viewport * fru * view).pretty_print() << std::endl;

    std::cout << "----------00000-------------" << std::endl;
    auto transform = trans_f::view(vec3f(0, 0, 0), vec3f(0, 0, 1), vec3f(0, 1, 0), err);
    std::cout << transform.pretty_print() << std::endl;

    transform = Transform<float>::frustum(RAD(75), 1, 1, 0.1) * transform;
    std::cout << Transform<float>::frustum(RAD(70), 1, 1000, 0.1).pretty_print() <<std::endl;

    //transform = trans_f::orthographic(-1, 1, -1, 1, 1, -1) * transform;
    std::cout << "-----------------------" << std::endl;

    std::cout << "-----------------------" << std::endl;

    transform = Transform<float>::viewport(100, 100) * transform;
    std::cout << Transform<float>::viewport(100, 100).pretty_print() <<std::endl;
    std::cout << "-----------------------" << std::endl;
    std::cout << transform.pretty_print() << std::endl << (transform * vt).pretty_print() << (err ? "err" : "success");
}
