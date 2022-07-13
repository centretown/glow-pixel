// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Color.h"
#include "Filter.h"

using glow::Filter;

namespace pixel
{
    class ColorFilter : public Filter<Color>
    {
    private:
        virtual void apply(Color &source, Color &color) = 0;
    };
}