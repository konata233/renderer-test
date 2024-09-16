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

void Renderer::append_mesh(const Mesh<float>& mesh) {
    this->meshes.push_back(mesh);
}

void Renderer::render_all() {
    for (Mesh<float> m : meshes) {
        m.render_mesh(&this->frame_buffer, &this->z_buffer);
    }
}
