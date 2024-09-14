//
// Created on 2024/9/13.
//

#ifndef RENDERER_COMMON_H
#define RENDERER_COMMON_H


#include <string>
#include "Color.h"

class Stringify {
public:
    virtual std::string stringify() = 0;
};

class PrettyPrint {
public:
    virtual std::string pretty_print() = 0;
};


#endif //RENDERER_COMMON_H
