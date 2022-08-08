// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Color.h"
#include "Filter.h"

using glow::Filter;

using color::Color;

namespace pixel
{
    class ColorFilter : public Filter<Color>
    {
    private:
        virtual void apply(Color &source) = 0;
    };
}