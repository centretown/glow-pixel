// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "Activity.h"
#include "Grid.h"
#include "GradientFilter.h"
#include "GradientPalette.h"
#include "HueFilter.h"
#include "SaturationFilter.h"
#include "LuminanceFilter.h"
#include "Controller.h"

using color::GradientPalette;
using color::hue_segment;
using glow::Activity;

extern pixel::Controller &Pixels;

namespace pixel
{
    class GradientActivity : public Activity
    {
    private:
        GradientPalette &palette;
        Grid &grid;

        HueFilter hueFilter;
        SaturationFilter saturationFilter;
        LuminanceFilter luminanceFilter;
        GradientFilter *filter;

        uint32_t next = 0;

        uint8_t state = 0;
        uint16_t counter = 0;
        uint16_t pulseWidth = 20;

    public:
        GradientActivity(GradientPalette &palette,
                      Grid &grid,
                      uint16_t pulseWidth = 20)
            : palette(palette), grid(grid), pulseWidth(pulseWidth)
        {
            Gradient &hue = palette.Hue();
            hue(0, hue_segment);
            Gradient &saturation = palette.Saturation();
            saturation(128, saturation_size);
            Gradient &luminance = palette.Luminance();
            luminance(1, 32);
            palette(0, saturation_size, luminance_size / 8);
            hueFilter.Setup(palette, grid);

            // luminanceFilter.Link(&slideFilter);
            // saturationFilter.Link(&slideFilter);
            filter = &hueFilter;
        }

        virtual void Reset() { next = 0; }
        virtual bool Ready()
        {
            auto now = Monitor::Now32();
            if (now >= next)
            {
                next = now + pulseWidth;
                return true;
            }
            return false;
        }
        virtual bool Done() { return false; }

        virtual void Update()
        {
            filter->Apply(palette);
            grid.SpinValues(Pixels, grid, palette);
            //     if (++counter > 1000)
            //     {
            //         counter = 0;
            //         State(++state);
            //     }
        }

        void State(uint8_t v)
        {
            if (v == 2)
            {
                filter = &luminanceFilter;
            }
            else if (v == 1)
            {
                filter = &saturationFilter;
            }
            else
            {
                v = 0;
                filter = &hueFilter;
            }

            state = v;
            filter->Setup(palette, grid);
        }

        inline uint16_t PulseWidth() const { return pulseWidth; }
        inline uint16_t PulseWidth(uint16_t v) { return pulseWidth = v; }
    };
}