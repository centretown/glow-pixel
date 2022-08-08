// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "GradientFilter.h"
#include "GradientPalette.h"
#include "Gradient.h"
#include "Filter.h"

using color::Gradient;
using color::GradientPalette;
using color::hue_limit;
using color::hue_size;
using color::saturation_size;
using color::VARY_SATURATION;
using glow::Filter;

namespace pixel
{
    class SaturationFilter : public GradientFilter
    {
    private:
        uint16_t hue = 0;

    public:
        virtual void Setup(GradientPalette &source, Grid &grid)
        {
            hue = 0;
            source(hue, 0, 15);
            source.Vary(VARY_SATURATION);
            Gradient &saturation = source.Saturation();
            saturation(3 * saturation_size / 4, saturation_size);
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
            source(hue, 0, 15);
        };
    };
}
