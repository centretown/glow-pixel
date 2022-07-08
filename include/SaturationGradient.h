// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Gradient.h"

namespace strip
{
    class SaturationGradient : public Gradient<uint8_t>
    {
    public:
        SaturationGradient(color_hsv_pack pack = 0,
                           bool gamma = false,
                           uint8_t span = (uint8_t)-1)
            : Gradient(pack, gamma, span) {}

        SaturationGradient(PixelColorHSV &colorHSV,
                           bool gamma = false,
                           uint8_t span = (uint8_t)-1)
            : Gradient(colorHSV, gamma, span) {}
            
        virtual color_pack Get(uint16_t index) { return 0; }
    };
} // namespace strip
