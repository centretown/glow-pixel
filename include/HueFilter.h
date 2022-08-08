// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "GradientFilter.h"
#include "GradientPalette.h"
#include "Gradient.h"
#include "Filter.h"

using glow::Filter;

using color::Gradient;
using color::GradientPalette;
using color::hue_limit;
using color::hue_red;
using color::hue_size;
using color::hue_yellow;
using color::saturation_size;
using color::VARY_HUE;

namespace pixel
{
    class HueFilter : public GradientFilter
    {
    public:
        virtual void Setup(GradientPalette &source, Grid &grid)
        {
            source(0, saturation_size, 15);
            source.Vary(VARY_HUE);
            Gradient hue = source.Hue();
            hue(hue_red, hue_yellow);
            source.Fit(grid);
        }

    private:
        virtual void apply(GradientPalette &source)
        {
            Gradient &hue = source.Hue();
            if (hue.End() >= hue_size)
            {
                hue <<= hue_limit;
            }
            hue >>= 2;
        }
    };
}