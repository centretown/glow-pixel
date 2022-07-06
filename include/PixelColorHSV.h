// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "PixelColor.h"
#include "pixel_base.h"

namespace strip
{
    const uint16_t max_color = 255;
    const uint16_t red_to_yellow = 255;
    const uint16_t red_to_green = 510;
    const uint16_t green_to_cyan = 765;
    const uint16_t green_to_blue = 1020;
    const uint16_t blue_to_magenta = 1275;
    const uint16_t blue_to_red = 1530;

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
            // fromRGB(color.Pack());
        }

        inline uint16_t Hue() { return hue; }
        inline void Hue(uint16_t v) { hue = v; }
        inline uint8_t Saturation() { return saturation; }
        inline void Saturation(uint8_t v) { saturation = v; }
        inline uint8_t Value() { return value; }
        inline void Value(uint8_t v) { value = v; }
        inline void HSV(uint16_t h, uint8_t s, uint8_t v)
        {
            hue = h;
            saturation = s;
            value = v;
        }

        color_pack ToRGB();
        // void fromRGB(color_pack rgb);

        // private:
        inline uint8_t biggest(PixelColor &color)
        {
            uint8_t colorMax = color.Red();
            if (color.Green() > colorMax)
            {
                colorMax = color.Green();
            }
            if (color.Blue() > colorMax)
            {
                colorMax = color.Blue();
            }
            return colorMax;
        }
        inline uint8_t smallest(PixelColor &color)
        {
            uint8_t colorMin = color.Red();
            if (color.Green() < colorMin)
            {
                colorMin = color.Green();
            }
            if (color.Blue() < colorMin)
            {
                colorMin = color.Blue();
            }
            return colorMin;
        }
        inline uint16_t mapHue()
        {
            uint32_t mapped_hue = hue * 1530L + 32768;
            mapped_hue /= 65536;
            return static_cast<uint16_t>(mapped_hue);
        }

        color_pack mapHueToColor(uint16_t mapped_hue)
        {
            if (mapped_hue < red_to_green)
            {
                return redToGreen(mapped_hue);
            }

            if (mapped_hue < green_to_blue)
            {
                return greenToBlue(mapped_hue);
            }

            if (mapped_hue < blue_to_red)
            {
                return blueToRed(mapped_hue);
            }

            // full red
            PixelColor color(max_color, 0, 0);
            return color.Pack();
        }

        inline color_pack redToGreen(uint16_t mapped_hue)
        {
            PixelColor color;
            if (mapped_hue < red_to_yellow)
            {
                color.Red(max_color);
                color.Green(static_cast<uint8_t>(mapped_hue));
            }
            else // yellow to green
            {
                color.Red(static_cast<uint8_t>(red_to_green - mapped_hue));
                color.Green(max_color);
            }
            return color.Pack();
        }

        inline color_pack greenToBlue(uint16_t mapped_hue)
        {
            PixelColor color;
            if (mapped_hue < green_to_cyan)
            {
                color.Green(max_color);
                color.Blue(static_cast<uint8_t>(mapped_hue - red_to_green));
            }
            else // cyan to blue
            {
                color.Green(static_cast<uint8_t>(green_to_blue - mapped_hue));
                color.Blue(max_color);
            }
            return color.Pack();
        }

        inline color_pack blueToRed(uint16_t mapped_hue)
        {
            PixelColor color;
            if (mapped_hue < blue_to_magenta)
            {
                color.Blue(max_color);
                color.Red(static_cast<uint8_t>(mapped_hue - green_to_blue));
            }
            else // magenta to red
            {
                color.Blue(static_cast<uint8_t>(blue_to_red - mapped_hue));
                color.Red(max_color);
            }
            return color.Pack();
        }

        color_pack applySaturationValue(color_pack pack)
        {
            uint16_t saturation_multiplier = 1 + saturation; // s1 1 to 256; same reason
            uint16_t value_multiplier = 1 + value;           // v1 1 to 256; allows >>8 instead of /255
            uint8_t saturation_added = 255 - saturation;     // s2 255 to 0

            PixelColor color(pack);

            uint8_t applied = apply(color.Red(),
                                    saturation_multiplier,
                                    value_multiplier,
                                    saturation_added);
            color.Red(applied);

            applied = apply(color.Green(),
                            saturation_multiplier,
                            value_multiplier,
                            saturation_added);
            color.Green(applied);

            applied = apply(color.Blue(),
                            saturation_multiplier,
                            value_multiplier,
                            saturation_added);
            color.Blue(applied);
            return color.Pack();
        }

        inline uint8_t apply(uint8_t color,
                             uint16_t saturation_multiplier,
                             uint16_t value_multiplier,
                             uint8_t saturation_added)
        {
            uint16_t color_result = color * saturation_multiplier;
            color_result >>= 8; // divide by 255
            color_result += saturation_added;
            color_result *= value_multiplier;
            color_result >>= 8; // shift to lower 8
            return static_cast<uint8_t>(color_result);
        }
    };

} // namespace strip
