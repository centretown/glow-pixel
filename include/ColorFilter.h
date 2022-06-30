// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelColor.h"
#include "Filter.h"

using glow::Filter;

namespace strip
{
    class ColorFilter : public Filter<PixelColor>
    {
    private:
        virtual void apply(PixelColor &source, PixelColor &color) = 0;
    };
}