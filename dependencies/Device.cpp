//
// Created on 2024/9/16.
//

#include "Device.h"
#include "Buffer.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "third-party/stb_image_write.h"


ImageOutputDevice::ImageOutputDevice() = default;

void ImageOutputDevice::bind_source(IColorBufferLike* buf) {
    this->buffer = buf;
}

void ImageOutputDevice::write_to_file(const char* filename) {
    unsigned int channels = 3;
    unsigned int width = this->buffer->width;
    unsigned int height = this->buffer->height;
    unsigned int size = this->buffer->size;

    auto* data = new unsigned char[size * channels];
    for (unsigned int i = 0; i < width; i++) {
        for (unsigned int j = 0; j < height; j++) {
            const Color* c = this->buffer->at_unsafe(i, j);
            data[width * j * channels + i * channels + 0] = static_cast<unsigned char>(c->r);
            data[width * j * channels + i * channels + 1] = static_cast<unsigned char>(c->g);
            data[width * j * channels + i * channels + 2] = static_cast<unsigned char>(c->b);
        }
    }
    stbi_write_png(filename, (int)width, (int)height, (int)channels, data, 0);
    delete[] data;
}
