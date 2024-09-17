//
// Created on 2024/9/15.
//

#include "Renderer.h"

Renderer::Renderer(unsigned int scr_width, unsigned int scr_height) : Renderer(scr_width, scr_height, 1) {

}

Renderer::Renderer(unsigned int scr_width, unsigned int scr_height, int msaa_scale) {
    this->screen = Screen(scr_width, scr_height);
    this->msaa_scale = msaa_scale;

    unsigned int msaa_width = scr_width * msaa_scale;
    unsigned int msaa_height = scr_height * msaa_scale;
    this->z_buffer = ZBuffer<float>(msaa_width, msaa_height);
    this->frame_buffer = FrameBuffer(msaa_width, msaa_height, Color(0, 0, 0, 1));
}

Renderer* Renderer::append_mesh(const Mesh<float>& mesh) {
    this->meshes.push_back(mesh);
    return this;
}

void Renderer::render_all() {
    for (Mesh<float>& m : meshes) {
        m.render_mesh(&this->frame_buffer, &this->z_buffer);
    }

    unsigned int scr_width = this->screen.width;
    unsigned int scr_height = this->screen.height;

    unsigned int scale = this->msaa_scale;
    auto scale_mul = static_cast<float>(1.0f / pow(scale, 2));

    if (scale != 1){
        for (unsigned int i = 0; i < scr_width; i++) {
            for (unsigned int j = 0; j < scr_height; j++) {
                Color color = Color();
                for (unsigned int s = 0; s < scale; s++){
                    for (unsigned int k = 0; k < scale; k++) {
                        color = color + *this->frame_buffer.at_unsafe(i * scale + s, j * scale + k) * scale_mul;
                    }
                }
                this->screen.set_unsafe(i, j, color);
            }
        }
    } else {
        for (unsigned int i = 0; i < scr_width; i++) {
            for (unsigned int j = 0; j < scr_height; j++) {
                this->screen.set_unsafe(i, j, *this->frame_buffer.at_unsafe(i, j));
            }
        }
    }
}

Screen* Renderer::get_screen_buffer() {
    return &this->screen;
}

FrameBuffer* Renderer::get_frame_buffer() {
    return &this->frame_buffer;
}
