// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "ColorFilter.h"

namespace glow
{
    class PixelDimmer : public ColorFilter
    {
    private:
        uint8_t intensity;

    public:
        PixelDimmer(uint8_t intensity = 100)
        {
            Intensity(intensity);
        }

        inline uint8_t Intensity() { return intensity; }
        inline void Intensity(uint8_t v)
        {
            if (v <= 100)
            {
                intensity = v;
            }
        }

        inline uint8_t Dim(uint8_t v) { return (intensity * v) / 100; }

        virtual PixelColor &Filter(PixelColor &source, PixelColor &color)
        {
            color.RGBW(Dim(source.Red()), Dim(source.Green()),
                       Dim(source.Blue()), Dim(source.White()));
            return color;
        }
    };
}