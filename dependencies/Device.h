//
// Created on 2024/9/16.
//

#ifndef RENDERER_DEVICE_H
#define RENDERER_DEVICE_H

#include <string>
#include "Common.h"
#include "Buffer.h"

class ImageOutputDevice {
public:
    void write_to_file(const char* filename);

    void bind_source(IColorBufferLike* buf);

    ImageOutputDevice();

protected:
    IColorBufferLike* buffer{};

};


#endif //RENDERER_DEVICE_H
