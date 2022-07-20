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
        color.Red(gamma8(color.Red()));
        color.Green(gamma8(color.Green()));
        color.Blue(gamma8(color.Blue()));
        color.White(gamma8(color.White()));
    }

    inline void Sine(Color &color)
    {
        color.Red(sine8(color.Red()));
        color.Green(sine8(color.Green()));
        color.Blue(sine8(color.Blue()));
        color.White(sine8(color.White()));
    }

    inline uint32_t base_pack(uint8_t r, uint8_t g, uint8_t b, uint8_t w)
    {
        return _basePixel::Color(r, g, b, w);
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