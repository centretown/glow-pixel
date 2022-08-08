// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Grid.h"
#include "GradientPalette.h"

using namespace color;

namespace pixel
{
    struct GridAttributes
    {
        uint16_t arrangement;
    };

    struct PaletteAttributes
    {
        Range hue;
        Range saturation;
        Range luminance;
    };

    class PixelState
    {
    private:
        PaletteAttributes *paletteAttributes;
        GridAttributes *gridAttributes;
        uint16_t size;

    public:
        PixelState(PaletteAttributes *paletteAttributes,
                   GridAttributes *gridAttributes, uint16_t size)
            : paletteAttributes(paletteAttributes),
              gridAttributes(gridAttributes),
              size(size) {}

        uint16_t Apply(uint16_t state, Grid &grid, GradientPalette &palette)
        {
            if (state & 1)
                grid.Rearrange(GRID_COLUMNS);
            else
                grid.Rearrange(GRID_ROWS);
            Gradient hue = palette.Hue();
            hue(hue_segment * state, hue_segment * state + 1);

            if (++state == size)
                state = 0;
            return state;
        }
    };
} // namespace pixel
