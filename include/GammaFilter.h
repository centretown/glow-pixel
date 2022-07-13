// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "ColorFilter.h"

namespace pixel
{
    class GammaFilter : public ColorFilter
    {
    private:
        virtual void apply(Color &source, Color &color)
        {
            color.Gamma(source);
        }
    };
}