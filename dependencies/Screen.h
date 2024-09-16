//
// Created on 2024/9/15.
//

#ifndef RENDERER_SCREEN_H
#define RENDERER_SCREEN_H


#include "Color.h"
#include "Buffer.h"

class Screen : public IColorBufferLike {
public:
    unsigned int width{};
    unsigned int height{};
    unsigned long size{};

    const Color* at(unsigned int idx_x, unsigned int idx_y, bool& error) override;

    const Color* at_unsafe(unsigned int idx_x, unsigned int idx_y) override;

    void set(unsigned int idx_x, unsigned int idx_y, const Color& color, bool& error);

    void set(unsigned int idx_x, unsigned int idx_y, char r, char g, char b, float a, bool& error);

    void set(unsigned int idx_x, unsigned int idx_y, char r, char g, char b, bool& error);

    void set_unsafe(unsigned int idx_x, unsigned int idx_y, const Color& color);

    void set_unsafe(unsigned int idx_x, unsigned int idx_y, char r, char g, char b, float a);

    void set_unsafe(unsigned int idx_x, unsigned int idx_y, char r, char g, char b);

    Screen() = default;

    ~Screen();

    explicit Screen(unsigned int scr_width, unsigned int scr_height);

protected:
    Color* data{};
};


#endif //RENDERER_SCREEN_H
