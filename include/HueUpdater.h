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
using color::luminance_size;
using color::saturation_size;
using color::VARY_HUE;
using glow::Source;
using glow::State;
using glow::Target;

namespace pixel
{
    class HueUpdater : public Source, public Target
    {
    protected:
        Grid &grid;
        GradientPalette &palette;
        uint16_t hue = 0;
        uint8_t saturation = saturation_size;
        uint8_t luminance = 15;

    public:
        HueUpdater(Grid &grid,
                   GradientPalette &palette,
                   uint16_t pulseWidth = 20)
            : grid(grid),
              palette(palette)
        {
            palette.Vary(VARY_HUE);
            saturation = palette.Saturation();
            luminance = palette.Luminance();
            palette.Fit(grid);
        }

        virtual uint32_t Update()
        {
            if (palette.End() >= hue_size)
            {
                palette <<= hue_limit;
            }
            palette >>= 2;

            grid.SpinValues(Pixels, grid, palette);
            return State(0, palette.Luminance()).Pack();
        }

        uint32_t Update(uint16_t status, uint16_t position)
        {
            if (position < luminance_size)
            {
                palette.Luminance(position);
            }
            // Update();
            return State(status, position).Pack();
        }
    };

} // namespace pixel
