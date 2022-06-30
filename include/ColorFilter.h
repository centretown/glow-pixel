// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelColor.h"
#include "Filter.h"

namespace glow
{
    class ColorFilter : public Filter<PixelColor>
    {
    private:
        virtual void apply(PixelColor &source, PixelColor &color) = 0;
    };
}