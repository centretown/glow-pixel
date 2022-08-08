// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "GradientPalette.h"
#include "Gradient.h"
#include "Grid.h"
#include "Filter.h"

using color::GradientPalette;
using glow::Filter;

namespace pixel
{
    class GradientFilter : public Filter<GradientPalette>
    {
    public:
        virtual void Setup(GradientPalette &source, Grid &grid) {}
    };
} // namespace pixel
