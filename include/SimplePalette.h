// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "ColorPalette.h"

namespace strip
{
    class SimplePalette : public ColorPalette
    {
    private:
        PixelColor *colors;
        uint16_t length;

    public:
        SimplePalette(PixelColor *colors, uint16_t length)
            : colors(colors), length(length) {}

        virtual PixelColor &Get(uint16_t index)
        {
            return colors[index % length];
        }
    };
} // namespace strip
