// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"

namespace glow
{
    class PixelMapper
    {
    protected:
        uint16_t pixelCount;

    public:
        PixelMapper(uint16_t pixelCount) : pixelCount(pixelCount) {}
        inline uint16_t PixelCount() { return pixelCount; }
        virtual uint16_t Get(uint16_t index) = 0;
    };
}
