//
// Created on 2024/9/13.
//

#ifndef RENDERER_COLOR_H
#define RENDERER_COLOR_H

#include "Common.h"

class Color {
public:
    char r;
    char g;
    char b;
    float a;

    Color(char red, char green, char blue, float alpha);
    Color(char red, char green, char blue);
    ~Color();
    Color();
};

class ToRGB {
public:
    virtual Color to_rgb() = 0;
};

class ColorHSV : public ToRGB {
public:
    unsigned short h;
    char s;
    char v;
    float a;

    Color to_rgb() override;

    ColorHSV();
    ColorHSV(unsigned short hue, char saturation, char value, float alpha);
    ColorHSV(unsigned short hue, char saturation, char value);
    ~ColorHSV();
};

class ColorHSL : public ToRGB {
public:
    unsigned short h;
    char s;
    char l;
    float a;

    Color to_rgb() override;

    ColorHSL();
    ColorHSL(unsigned short hue, char saturation, char lightness, float alpha);
    ColorHSL(unsigned short hue, char saturation, char lightness);
    ~ColorHSL();
};

#endif //RENDERER_COLOR_H
