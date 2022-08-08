// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelActivity.h"
#include "Grid.h"
#include "GradientPalette.h"
#include "Controller.h"

extern pixel::Controller &Pixels;
using color::GradientPalette;
using glow::Activity;

uint16_t const fill_size = 3;

namespace pixel
{
    class SlideActivity : public PixelActivity<Grid, GradientPalette>
    {
    private:
        Range section;
        color_pack fill[fill_size];
        color_pack color;

    public:
        SlideActivity(Grid &grid,
                      GradientPalette &palette,
                      uint16_t pulseWidth)
            : PixelActivity<Grid, GradientPalette>(grid, palette, pulseWidth)
        {
            section(grid.Begin(), grid.Begin() + fill_size);
            Refill();
            color = Color(0, 63, 63).Pack();
        }

        virtual void Update()
        {
            Fill();
            section >>= 1;
            if (section.End() > grid.End())
            {
                section(grid.Begin(), grid.Begin() + section.Length());
            }

            Refill();
            palette.Fit(section);
            section.SpinValues(Pixels, grid, palette);
        }

        inline void Fill()
        {
            uint16_t j = 0;
            for (uint16_t i = section.Begin(); i < section.End(); i++, j++)
            {
                Pixels.Put(grid.Map(i), fill[j]);
            }
        }
        inline void Refill()
        {
            uint16_t j = 0;
            for (uint16_t i = section.Begin(); i < section.End(); i++, j++)
            {
                fill[j] = Pixels.Get(grid.Map(i));
            }
        }
    };

} // namespace pixel
