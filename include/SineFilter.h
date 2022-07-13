// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "ColorFilter.h"

namespace pixel
{
    class SineFilter : public ColorFilter
    {
    private:
        virtual void apply(Color &source, Color &color)
        {
            color.Sine(source);
        }
    };
}
