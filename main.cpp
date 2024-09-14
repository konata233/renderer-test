#include <iostream>
#include "dependencies/Vector.h"
#include "dependencies/Matrix.h"

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

    bool err;

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
    std::cout << mul.pretty_print();
    /*
    int l, l2;
    std::cin >> l >> l2;
    int arr[l][l2];
    auto ptr = arr;
    auto ptr2 = *ptr;
    for (int i = 0; i < l * l2; i++) {
        *ptr2 = i;
        ptr2++;
    }
    std::cout << (ptr2 - l * l2)[11];
    return 0;*/
}
