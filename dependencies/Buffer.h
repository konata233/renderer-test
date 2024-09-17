//
// Created on 2024/9/15.
//

#ifndef RENDERER_BUFFER_H
#define RENDERER_BUFFER_H


#include <cmath>
#include "Color.h"

class IColorBufferLike {
public:
    unsigned int width{};

    unsigned int height{};

    unsigned int size{};

    virtual const Color* at(unsigned int idx_x, unsigned int idx_y, bool& error) = 0;

    virtual const Color* at_unsafe(unsigned int idx_x, unsigned int idx_y) = 0;
};

template <class T>
class ZBuffer {
public:
    unsigned int width;
    unsigned int height;
    unsigned long size;

    T at(unsigned int w, unsigned int h, bool& error);

    T at_unsafe(unsigned int w, unsigned int h);

    void set(unsigned int w, unsigned int h, T data, bool& error);

    void set_unsafe(unsigned int w, unsigned int h, T data);

    bool check(unsigned int w, unsigned int h, T new_data);

    bool set_check(unsigned int w, unsigned h, T new_data);

    ZBuffer();

    ~ZBuffer();

    ZBuffer(unsigned int width, unsigned int height);

    ZBuffer(unsigned int width, unsigned int height, T* data_init);

protected:
    T* buffer;
};

template <class T>
ZBuffer<T>::~ZBuffer() = default;

template <class T>
bool ZBuffer<T>::set_check(unsigned int w, unsigned int h, T new_data) {
    bool flag = check(w, h, new_data);
    if (flag) {
        this->set_unsafe(w, h, new_data);
    }
    return flag;
}

template <class T>
bool ZBuffer<T>::check(unsigned int w, unsigned int h, T new_data) {
    T current = this->at_unsafe(w, h);
    return (new_data < current || current == INFINITY);
}

template <class T>
void ZBuffer<T>::set_unsafe(unsigned int w, unsigned int h, T data) {
    this->buffer[h * this->width + w] = data;
}

template <class T>
void ZBuffer<T>::set(unsigned int w, unsigned int h, T data, bool& error) {
    if (w >= this->width || h >= this->height) {
        error = true;
        return;
    } else {
        error = false;
        this->set_unsafe(w, h, data);
    }
}

template <class T>
T ZBuffer<T>::at(unsigned int w, unsigned int h, bool& error) {
    if (w >= this->width || h >= this->height) {
        error = true;
        return INFINITY;
    } else {
        error = false;
        return this->at_unsafe(w, h);
    }
}

template <class T>
T ZBuffer<T>::at_unsafe(unsigned int w, unsigned int h) {
    return this->buffer[h * this->width + w];
}

template <class T>
ZBuffer<T>::ZBuffer(unsigned int width, unsigned int height, T* data_init) {
    this->width = width;
    this->height = height;
    this->size = width * height;
    this->buffer = new T[this->size];
    for (unsigned long i = 0; i < this->size; i++) {
        this->buffer[i] = data_init[i];
    }
}

/// Initialize the buffer elements to +inf (!!)
/// \tparam T
/// \param width
/// \param height
template <class T>
ZBuffer<T>::ZBuffer(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
    this->size = width * height;
    this->buffer = new T[this->size];
    for (unsigned long i = 0; i < this->size; i++) {
        this->buffer[i] = INFINITY;
    }
}

template <class T>
ZBuffer<T>::ZBuffer() {
    this->width = 0;
    this->height = 0;
    this->size = 0;
    this->buffer = nullptr;
}

class FrameBuffer : public IColorBufferLike {
public:
    unsigned int width;
    unsigned int height;
    unsigned long size;

    const Color* at(unsigned int w, unsigned int h, bool& error) override;

    const Color* at_unsafe(unsigned int w, unsigned int h) override;

    void set(unsigned int w, unsigned int h, const Color& data, bool& error);

    void set_unsafe(unsigned int w, unsigned int h, const Color& data);

    FrameBuffer();

    ~FrameBuffer();

    FrameBuffer(unsigned int w, unsigned int h, const Color& bg);

    FrameBuffer(unsigned int w, unsigned int h, Color* data_init);

protected:
    Color* buffer;
};


#endif //RENDERER_BUFFER_H
