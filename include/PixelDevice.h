// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Updater.h"
#include "PixelColor.h"

using glow::Updater;

namespace strip
{
    class PixelDevice : public Updater
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
        virtual void Put(uint16_t index, color_pack color) = 0;
    };
}