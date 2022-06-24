// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelColor.h"

namespace glow
{
    class ColorFilter
    {
    private:
        ColorFilter *next = NULL;

    public:
        virtual PixelColor &Apply(PixelColor &source, PixelColor &color)
        {
            color.Copy(source);
            return color;
        }

        void Link(ColorFilter *f)
        {
            next = f;
        }
    };
}