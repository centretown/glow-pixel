// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Color.h"
#include "Mapper.h"

using glow::Mapper;

namespace pixel
{
    class ColorPalette : public Mapper<color_pack>
    {
    public:
        virtual color_pack Get(uint16_t index) = 0;
    };
}