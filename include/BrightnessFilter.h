// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "ColorFilter.h"

namespace strip
{
    class BrightnessFilter : public ColorFilter
    {
    private:
        uint8_t intensity;

    public:
        BrightnessFilter(uint8_t intensity = 100)
        {
            Intensity(intensity);
        }

        inline uint8_t Intensity() { return intensity; }
        inline void Intensity(uint8_t v)
        {
            intensity = (v > 100) ? 100 : v;
        }

    private:
        inline uint8_t dim(uint8_t v) { return (intensity * v) / 100; }
        virtual void apply(PixelColor &source, PixelColor &color)
        {
            color.RGBW(dim(source.Red()), dim(source.Green()),
                       dim(source.Blue()), dim(source.White()));
        }
    };
}