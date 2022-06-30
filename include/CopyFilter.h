// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "ColorFilter.h"

namespace strip
{
    class CopyFilter : public ColorFilter
    {
    private:
        virtual void apply(PixelColor &source, PixelColor &color)
        {
            color.Copy(source);
        }
    };
}
