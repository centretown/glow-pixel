// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Controller.h"
#include "Grid.h"
#include "Updater.h"
#include "GradientPalette.h"

extern pixel::Controller &Pixels;

using color::GradientPalette;
using color::GradientVaried;
using color::hue_limit;
using color::hue_segment;
using color::hue_size;
using color::luminance_size;
using color::saturation_size;
using color::VARY_HUE;
using color::VARY_LUMINANCE;
using color::VARY_SATURATION;
using glow::Source;
using glow::Target;
using glow::State;

namespace pixel
{
    const uint8_t vary_limit = VARY_LUMINANCE + 1;
    class GradientUpdater : public Target, public Source
    {
    protected:
        Grid &grid;
        GradientPalette &palette;
        uint16_t pulseWidth = 20;
        uint16_t hue = 0;
        uint8_t saturation = saturation_size;
        uint8_t luminance = 15;

    public:
        GradientUpdater(Grid &grid,
                        GradientPalette &palette,
                        uint16_t pulseWidth = 20)
            : grid(grid),
              palette(palette),
              pulseWidth(pulseWidth)
        {
            palette.Vary(VARY_HUE);
            saturation = palette.Saturation();
            luminance = palette.Luminance();
            palette.Fit(grid);
        }

        // Source
        inline uint32_t Update()
        {
            grid.SpinValues(Pixels, grid, palette);
            return pulseWidth;
        }
        
        // Target
        inline uint32_t Update(uint16_t status, uint16_t position)
        {
            status %= vary_limit;
            auto v = palette.Vary((GradientVaried)status);
            if (position > palette.Size())
            {
                position = palette.Size();
            }
            switch (v)
            {
            case VARY_HUE:
                palette.Saturation(position);
                palette(palette.Hue(), palette.Hue() + 255);
                break;
            case VARY_SATURATION:
                palette.Luminance(position);
                palette(palette.Size() / 2, palette.Size());
                break;
            case VARY_LUMINANCE:
            default:
                palette(0, palette.Size());
                palette.Hue(position);
                break;
            }
            return State(status, position).Pack();
        }
    };

} // namespace pixel
