// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "pixel_base.h"

#include "Color.h"
using color::Color;

namespace pixel
{
    inline void Gamma(Color &color)
    {
        color.RGBW(gamma8(color.Red()),
                   gamma8(color.Green()),
                   gamma8(color.Blue()),
                   gamma8(color.White()));
    }

    inline void Sine(Color &color)
    {
        color.RGBW(sine8(color.Red()),
                   sine8(color.Green()),
                   sine8(color.Blue()),
                   sine8(color.White()));
    }

    inline uint32_t base_pack(uint8_t red, uint8_t green, uint8_t blue, uint8_t white=0)
    {
        return _basePixel::Color(red, green, blue, white);
    }

    inline uint32_t base_hsv(uint16_t hue, uint8_t saturation = 255, uint8_t value = 255)
    {
        return _basePixel::ColorHSV(hue, saturation, value);
    }
    inline uint8_t gamma8(uint8_t c)
    {
        return _basePixel::gamma8(c);
    }
    inline uint8_t sine8(uint8_t c)
    {
        return _basePixel::sine8(c);
    }
}