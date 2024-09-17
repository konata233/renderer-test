//
// Created on 2024/9/15.
//

#include "Screen.h"

const Color* Screen::at(unsigned int idx_x, unsigned int idx_y, bool& error) {
    if (idx_x >= width || idx_y >= height) {
        error = true;
        return nullptr;
    } else {
        error = false;
        return at_unsafe(idx_x, idx_y);
    }
}

void Screen::set(unsigned int idx_x, unsigned int idx_y, const Color& color, bool& error) {
    if (idx_x >= width || idx_y >= height) {
        error = true;
    } else {
        error = false;
        set_unsafe(idx_x, idx_y, color);
    }
}

void Screen::set_unsafe(unsigned int idx_x, unsigned int idx_y, const Color& color) {
    this->data[idx_y * width + idx_x] = color.copy();
}

const Color* Screen::at_unsafe(unsigned int idx_x, unsigned int idx_y) {
    const Color* ptr = &(this->data[idx_y * width + idx_x]);
    return ptr;
}

void Screen::set(unsigned int idx_x, unsigned int idx_y, char r, char g, char b, float a, bool& error) {
    set(idx_x, idx_y, Color(r, g, b, a), error);
}

void Screen::set(unsigned int idx_x, unsigned int idx_y, char r, char g, char b, bool& error) {
    set(idx_x, idx_y, r, g, b, 1.0, error);
}

void Screen::set_unsafe(unsigned int idx_x, unsigned int idx_y, char r, char g, char b, float a) {
    set_unsafe(idx_x, idx_y, Color(r, g, b, a));
}

void Screen::set_unsafe(unsigned int idx_x, unsigned int idx_y, char r, char g, char b) {
    set_unsafe(idx_x, idx_y, r, g, b, 1.0);
}

Screen::Screen(unsigned int scr_width, unsigned int scr_height) {
    this->width = scr_width;
    this->height = scr_height;
    this->size = scr_width * scr_height;

    this->data = new Color[this->size];
    for (unsigned long i = 0; i < this->size ; i++) {
        data[i] = Color();
    }
}

Screen::~Screen() = default;
