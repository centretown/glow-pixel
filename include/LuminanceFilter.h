// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "GradientFilter.h"
#include "GradientPalette.h"
#include "Gradient.h"
#include "Grid.h"
#include "Filter.h"

using color::Gradient;
using color::GradientPalette;
using color::hue_limit;
using color::hue_size;
using color::luminance_size;
using color::saturation_size;
using color::VARY_LUMINANCE;
using glow::Filter;

namespace pixel
{
    class LuminanceFilter : public GradientFilter
    {
    private:
        uint16_t hue = 0;

    public:
        virtual void Setup(GradientPalette &source, Grid &grid)
        {
            hue = 0;
            source(hue, saturation_size, 15);
            source.Vary(VARY_LUMINANCE);
            Gradient &luminance = source.Luminance();
            luminance(1, luminance_size / 8);
            source.Fit(grid);
        }

    private:
        virtual void apply(GradientPalette &source)
        {
            ++hue;
            if (hue >= hue_size)
            {
                hue = hue_limit;
            }
            source(hue, saturation_size, 0);
        };
    };
}
