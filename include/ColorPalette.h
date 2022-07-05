// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelColor.h"
#include "Mapper.h"

using glow::Mapper;

namespace strip
{
    class ColorPalette : public Mapper<color_pack>
    {
    public:
        virtual color_pack Get(uint16_t index) = 0;
    };
}