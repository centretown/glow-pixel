// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "ColorPalette.h"

namespace pixel
{
    class SimplePalette : public ColorPalette
    {
    private:
        color_pack *colors;
        uint16_t length;

    public:
        SimplePalette(color_pack *colors, uint16_t length)
            : colors(colors), length(length) {}

        virtual color_pack Get(uint16_t index)
        {
            return colors[index % length];
        }
    };
} // namespace pixel
