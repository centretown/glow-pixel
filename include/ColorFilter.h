// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelColor.h"

namespace glow
{
    class ColorFilter
    {
    public:
        virtual PixelColor &Filter(PixelColor &source, PixelColor &color) = 0;
    };
}