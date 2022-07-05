// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "pixel_base.h"

namespace strip
{
    typedef struct
    {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint8_t white;
    } PixelRGBW;

    class PixelColor
    {
    private:
        union
        {
            PixelRGBW rgbw;
            uint32_t value;
        };

    public:
        PixelColor(
            uint8_t red = 0,
            uint8_t green = 0,
            uint8_t blue = 0,
            uint8_t white = 0)
        {
            rgbw.red = red;
            rgbw.green = green;
            rgbw.blue = blue;
            rgbw.white = white;
        }

        PixelColor(PixelColor &color)
        {
            rgbw.red = color.rgbw.red;
            rgbw.green = color.rgbw.green;
            rgbw.blue = color.rgbw.blue;
            rgbw.white = color.rgbw.white;
        }

        // access member

        inline uint8_t Red() { return rgbw.red; }
        inline uint8_t Green() { return rgbw.green; }
        inline uint8_t Blue() { return rgbw.blue; }
        inline uint8_t White() { return rgbw.white; }
        inline uint32_t Value() { return value; }

        // modify member

        inline void Red(uint8_t r) { rgbw.red = r; }
        inline void Green(uint8_t g) { rgbw.green = g; }
        inline void Blue(uint8_t b) { rgbw.blue = b; }
        inline void White(uint8_t w) { rgbw.white = w; }

        // modify all members

        inline void Value(uint32_t v) { value = v; }

        inline void RGB(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0)
        {
            RGBW(r, g, b);
        }
        inline void GBR(uint8_t g = 0, uint8_t b = 0, uint8_t r = 0)
        {
            RGBW(r, g, b);
        }
        inline void BGR(uint8_t b = 0, uint8_t g = 0, uint8_t r = 0)
        {
            RGBW(r, g, b);
        }

        inline void RGBW(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t w = 0)
        {
            rgbw.red = r;
            rgbw.green = g;
            rgbw.blue = b;
            rgbw.white = w;
        }

        inline void UnPack(uint32_t packed)
        {
            const uint32_t mask = 0x000000ff;
            rgbw.blue = packed & mask;
            rgbw.green = (packed >> 8) & mask;
            rgbw.red = (packed >> 16) & mask;
            rgbw.white = (packed >> 24) & mask;
        }

        inline void Hue(uint16_t hue, uint8_t saturation = 255, uint8_t value = 255)
        {
            UnPack(hsv(hue, saturation, value));
        }

        // misc.
        inline uint32_t Pack()
        {
            return pack(rgbw.red, rgbw.green, rgbw.blue, rgbw.white);
        }

        // filter functions (modify all)
        inline void Copy(PixelColor &color)
        {
            rgbw.red = color.rgbw.red;
            rgbw.green = color.rgbw.green;
            rgbw.blue = color.rgbw.blue;
            rgbw.white = color.rgbw.white;
        }

        inline void Gamma(PixelColor &color)
        {
            rgbw.red = gamma8(color.rgbw.red);
            rgbw.green = gamma8(color.rgbw.green);
            rgbw.blue = gamma8(color.rgbw.blue);
            rgbw.white = gamma8(color.rgbw.white);
        }

        inline void Sine(PixelColor &color)
        {
            rgbw.red = sine8(color.rgbw.red);
            rgbw.green = sine8(color.rgbw.green);
            rgbw.blue = sine8(color.rgbw.blue);
            rgbw.white = sine8(color.rgbw.white);
        }

    private:
        inline uint32_t hsv(uint16_t hue, uint8_t saturation = 255, uint8_t value = 255)
        {
            return _basePixel::ColorHSV(hue, saturation, value);
        }
        inline uint32_t pack(uint8_t r, uint8_t g, uint8_t b, uint8_t w)
        {
            return _basePixel::Color(r, g, b, w);
        }
        inline uint8_t gamma8(uint8_t c)
        {
            return _basePixel::gamma8(c);
        }
        inline uint8_t sine8(uint8_t c)
        {
            return _basePixel::sine8(c);
        }
    };
}