// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Controller.h"
#include "Grid.h"
#include "GradientPalette.h"
#include "Updater.h"
#include "State.h"

extern pixel::Controller &Pixels;

using color::GradientPalette;
using color::hue_limit;
using color::hue_segment;
using color::hue_size;
using color::saturation_size;
using color::VARY_LUMINANCE;

using glow::Source;
using glow::Target;
using glow::State;

namespace pixel
{
    class LuminanceUpdater : public Source, public Target
    {
    protected:
        Grid &grid;
        GradientPalette &palette;
        uint16_t pulseWidth = 20;
        uint16_t hue = 0;

    public:
        LuminanceUpdater(Grid &grid,
                         GradientPalette &palette,
                         uint16_t pulseWidth = 20)
            : grid(grid),
              palette(palette),
              pulseWidth(pulseWidth)
        {
            palette.Vary(VARY_LUMINANCE);
            hue = palette.Hue();
            palette.Fit(grid);
        }

        virtual uint32_t Update()
        {
            ++hue;
            if (hue >= hue_size)
            {
                hue = hue_limit;
            }

            grid.SpinValues(Pixels, grid, palette);
            return pulseWidth;
        }

        uint32_t Update(uint16_t status, uint16_t position)
        {
            if (position < hue_size)
            {
                palette.Hue(position);
            }
            return State(status, position).Pack();
        }
    };

} // namespace pixel
