//
// Created on 2024/9/13.
//

#include <cmath>
#include "Color.h"

#define RANGE(_v, _x, _y) (_v >= _x && _v < _y)

Color::Color() : r(0), g(0), b(0), a(1.0) {

}

Color::Color(float red, float green, float blue, float alpha) : r(red), g(green), b(blue), a(alpha) {

}

Color::Color(float red, float green, float blue) : Color(red, green, blue, 1.0) {

}

Color Color::copy() const {
    return {this->r, this->g, this->b, this->a};
}

Color Color::operator*(float rhs) const {
    Color color;
    color.a = 1;
    color.r = std::min(this->r * rhs, 255.0f);
    color.g = std::min(this->g * rhs, 255.0f);
    color.b = std::min(this->b * rhs, 255.0f);
    return color;
}

Color Color::operator+(const Color& rhs) const {
    Color color;
    color.a = 1;
    color.r = std::min(this->r + rhs.r, 255.0f);
    color.g = std::min(this->g + rhs.g, 255.0f);
    color.b = std::min(this->b + rhs.b, 255.0f);
    return color;
}

Color::~Color() = default;

ColorHSV::ColorHSV() : h(0), s(100), v(100), a(1.0) {

}

ColorHSV::ColorHSV(unsigned short hue, float saturation, float value, float alpha) : h(hue), s(saturation), v(value),
                                                                                     a(alpha) {

}

ColorHSV::ColorHSV(unsigned short hue, float saturation, float value) : ColorHSV(hue, saturation, value, 1.0) {

}

Color ColorHSV::to_rgb() {
    Color color = Color();
    double c = v * s;
    double x = c * (1 - std::fabs((h / 60) % 2 - 1));
    double m = v - c;
    double rt, gt, bt;

    if (RANGE(h, 0, 60) || RANGE(h, 300, 360)) {
        rt = c;
    } else if (RANGE(h, 60, 120) || RANGE(h, 240, 300)) {
        rt = x;
    } else {
        rt = 0;
    }

    if (RANGE(h, 0, 60) || RANGE(h, 180, 240)) {
        gt = x;
    } else if (RANGE(h, 60, 180)) {
        gt = c;
    } else {
        gt = 0;
    }

    if (RANGE(h, 120, 180) || RANGE(h, 300, 360)) {
        bt = x;
    } else if (RANGE(h, 180, 300)) {
        bt = c;
    } else {
        bt = 0;
    }

    color.r = static_cast<float>((rt + m) * 255);
    color.g = static_cast<float>((gt + m) * 255);
    color.b = static_cast<float>((bt + m) * 255);
    color.a = this->a;

    return color;
}

ColorHSV::~ColorHSV() = default;

ColorHSL::ColorHSL() : h(0), s(100), l(100), a(1.0) {

}

ColorHSL::ColorHSL(unsigned short hue, float saturation, float lightness, float alpha) : h(hue), s(saturation),
                                                                                         l(lightness), a(alpha) {

}

ColorHSL::ColorHSL(unsigned short hue, float saturation, float lightness) : ColorHSL(hue, saturation, lightness, 1.0) {

}

Color ColorHSL::to_rgb() {
    // todo
    return {};
}

ColorHSL::~ColorHSL() = default;
