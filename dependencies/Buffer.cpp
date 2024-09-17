//
// Created on 2024/9/15.
//

#include "Buffer.h"

FrameBuffer::FrameBuffer() {
    this->width = 0;
    this->height = 0;
    this->size = 0;
    this->buffer = nullptr;
}

FrameBuffer::FrameBuffer(unsigned int w, unsigned int h, const Color& bg) {
    this->width = w;
    this->height = h;
    this->size = w * h;
    this->buffer = new Color[size];

    auto color = bg.copy();
    for (unsigned long i = 0; i < this->size; i++) {
        buffer[i] = color.copy();
    }
}

FrameBuffer::FrameBuffer(unsigned int w, unsigned int h, Color* data_init) {
    this->width = w;
    this->height = h;
    this->size = w * h;
    this->buffer = new Color[this->size];

    for (unsigned long i = 0; i < this->size; i++) {
        this->buffer[i] = data_init[i].copy();
    }
}

const Color* FrameBuffer::at_unsafe(unsigned int w, unsigned int h) {
    return &this->buffer[h * this->width + w];
}

const Color* FrameBuffer::at(unsigned int w, unsigned int h, bool& error) {
    if (w >= this->width || h >= this->height) {
        error = true;
        return nullptr;
    } else {
        error = false;
        return at_unsafe(w, h);
    }
}

void FrameBuffer::set(unsigned int w, unsigned int h, const Color& data, bool& error) {
    if (w >= this->width || h >= this->height) {
        error = true;
        return;
    } else {
        error = false;
        set_unsafe(w, h, data);
    }
}

void FrameBuffer::set_unsafe(unsigned int w, unsigned int h, const Color& data) {
    this->buffer[h * this->width + w] = data.copy();
}

FrameBuffer::~FrameBuffer() = default;
