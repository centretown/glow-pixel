// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelColor.h"
#include "pixel_base.h"

namespace strip
{
    class PixelColorHSV
    {
    private:
        uint16_t hue;
        uint8_t saturation;
        uint8_t value;

    public:
        PixelColorHSV(uint16_t hue = 0xffff,
                      uint8_t saturation = 0xff,
                      uint8_t value = 0xff)
            : hue(hue), saturation(saturation), value(value) {}

        PixelColorHSV(PixelColor &color)
        {
            fromRGB(color);
        }

        inline uint16_t Hue() { return hue; }
        inline void Hue(uint16_t v) { hue = v; }
        inline uint8_t Saturation() { return saturation; }
        inline void Saturation(uint8_t v) { saturation = v; }
        inline uint8_t Value() { return value; }
        inline void Value(uint8_t v) { value = v; }

        PixelColor &RGB(PixelColor &color)
        {
            return color;
        }

        void fromRGB(PixelColor &color);

    private:
        inline uint8_t findMax(PixelColor &color)
        {
            uint8_t cmax = color.Red();
            if (color.Green() > cmax)
            {
                cmax = color.Green();
            }
            if (color.Blue() > cmax)
            {
                cmax = color.Blue();
            }
            return cmax;
        }
        inline uint8_t findMin(PixelColor &color)
        {
            uint8_t cmin = color.Red();
            if (color.Green() < cmin)
            {
                cmin = color.Green();
            }
            if (color.Blue() < cmin)
            {
                cmin = color.Blue();
            }
            return cmin;
        }
    };

} // namespace strip
