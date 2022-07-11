// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "PixelController.h"

namespace strip
{
    extern const uint8_t device_count;
    extern const uint16_t pixel_count;
    extern const pixel_index *pixelIndex;

    extern PixelDevice *pixelDevices[];
    extern PixelController &Pixels;

    pixel_index *buildIndex(pixel_index *index,
                            const uint16_t pixelCount,
                            const uint16_t *partitions);
}
