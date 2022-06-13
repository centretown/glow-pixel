// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"

class PixelDimmer
{
private:
    uint8_t intensity;

public:
    PixelDimmer(uint8_t intensity = 100)
    {
        Intensity(intensity);
    }
    inline uint8_t Intensity() { return intensity; }
    inline void Intensity(uint8_t v)
    {
        if (v <= 100)
        {
            intensity = v;
        }
    }
    inline uint8_t Dim(uint8_t c) { return (intensity * c) / 100; }
};
