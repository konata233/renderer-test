//
// Created on 2024/9/13.
//

#ifndef RENDERER_COLOR_H
#define RENDERER_COLOR_H

#include "Common.h"

class Color {
public:
    float r;
    float g;
    float b;
    float a;

    Color copy() const; // NOLINT(*-use-nodiscard)

    Color(float red, float green, float blue, float alpha);

    Color(float red, float green, float blue);

    Color operator*(float rhs) const;

    Color operator+(const Color& rhs) const;

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
    float s;
    float v;
    float a;

    Color to_rgb() override;

    ColorHSV();

    ColorHSV(unsigned short hue, float saturation, float value, float alpha);

    ColorHSV(unsigned short hue, float saturation, float value);

    ~ColorHSV();
};

class ColorHSL : public ToRGB {
public:
    unsigned short h;
    float s;
    float l;
    float a;

    Color to_rgb() override;

    ColorHSL();

    ColorHSL(unsigned short hue, float saturation, float lightness, float alpha);

    ColorHSL(unsigned short hue, float saturation, float lightness);

    ~ColorHSL();
};

#endif //RENDERER_COLOR_H
