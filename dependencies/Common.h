//
// Created on 2024/9/13.
//

#ifndef RENDERER_COMMON_H
#define RENDERER_COMMON_H


#include <string>

class IStringify {
public:
    virtual std::string stringify() = 0;
};

class IPrettyPrint {
public:
    virtual std::string pretty_print() = 0;
};

#endif //RENDERER_COMMON_H
