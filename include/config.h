// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "Controller.h"

namespace pixel
{
    extern const uint8_t device_count;
    extern const uint16_t pixel_count;
    extern const pixel_index *pixelIndex;

    extern Device pixelDevices[];
    extern Controller &Pixels;

    pixel_index *buildIndex(pixel_index *index,
                            const uint16_t pixelCount,
                            const uint16_t *partitions);
}
