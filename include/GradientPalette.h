// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "ColorPalette.h"
#include "ColorHSV.h"

namespace pixel
{
    class GradientPalette : public ColorPalette
    {
    private:
        ColorHSV hsv;
        bool gamma = false;

    public:
        GradientPalette(color_hsv_pack pack = 0,
                        bool gamma = false)
            : gamma(gamma)
        {
            hsv.Pack(pack);
        }

        GradientPalette(ColorHSV &colorHSV,
                        bool gamma = false)
            : GradientPalette(colorHSV.Pack(), gamma) {}

        // accessors
        inline ColorHSV &HSV() { return hsv; }
        inline bool Gamma() { return gamma; }

        // updaters
        inline void Gamma(bool v) { gamma = v; }

        // virtual color_pack Get(uint16_t index) = 0;
    };

} // namespace pixel

