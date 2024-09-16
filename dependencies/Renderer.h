//
// Created on 2024/9/15.
//

#ifndef RENDERER_RENDERER_H
#define RENDERER_RENDERER_H

#include <vector>
#include "Mesh.h"
#include "Buffer.h"
#include "Screen.h"

class Renderer {
public:
    void append_mesh(const Mesh<float>& mesh);

    void render_all();

    Renderer(unsigned int scr_width, unsigned int scr_height);

    Renderer(unsigned int scr_width, unsigned int scr_height, int msaa_scale);

protected:
    std::vector<Mesh<float>> meshes;
    ZBuffer<float> z_buffer;
    FrameBuffer frame_buffer;
    Screen screen{};
    int msaa_scale;
};


#endif //RENDERER_RENDERER_H
