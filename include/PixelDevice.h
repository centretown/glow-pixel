// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelColor.h"

namespace glow
{
    class PixelDevice
    {
    protected:
        uint16_t pixelCount = 0;

    public:
        PixelDevice(uint16_t pixelCount = 0) : pixelCount(pixelCount) {}
        inline uint16_t PixelCount()
        {
            return pixelCount;
        }

        virtual void Setup() {}
        virtual void Put(uint16_t index, PixelColor &color) = 0;
        virtual void Update() = 0;
    };
}