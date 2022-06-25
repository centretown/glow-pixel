// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "ColorFilter.h"

namespace glow
{
    class GammaFilter : public ColorFilter
    {
    private:
        virtual void apply(PixelColor &source, PixelColor &color)
        {
            color.Gamma(source);
        }
    };
}