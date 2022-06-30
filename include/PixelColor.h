// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "pixel_base.h"

namespace strip
{
    class PixelColor
    {
    private:
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint8_t white;

    public:
        PixelColor(
            uint8_t red = 0,
            uint8_t green = 0,
            uint8_t blue = 0,
            uint8_t white = 0)
            : red(red), green(green), blue(blue), white(white) {}

        PixelColor(PixelColor &color)
        {
            red = color.red;
            green = color.green;
            blue = color.blue;
            white = color.white;
        }

        // modify member
        
        inline uint8_t Red() { return red; }
        inline void Red(uint8_t r) { red = r; }
        inline uint8_t Green() { return green; }
        inline void Green(uint8_t g) { green = g; }
        inline uint8_t Blue() { return blue; }
        inline void Blue(uint8_t b) { blue = b; }
        inline uint8_t White() { return white; }
        inline void White(uint8_t w) { white = w; }

        // modify all members

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
            red = r;
            green = g;
            blue = b;
            white = w;
        }

        inline void UnPack(uint32_t packed)
        {
            uint32_t mask = 0x000000ff;
            blue = packed & mask;
            green = (packed >> 8) & mask;
            red = (packed >> 16) & mask;
            white = (packed >> 24) & mask;
        }

        inline void Hue(uint16_t hue, uint8_t saturation = 255, uint8_t value = 255)
        {
            UnPack(hsv(hue, saturation, value));
        }

        // misc.
        inline uint32_t Pack()
        {
            return pack(red, green, blue, white);
        }

        // filter functions (modify all)
        inline void Copy(PixelColor &color)
        {
            red = color.red;
            green = color.green;
            blue = color.blue;
            white = color.white;
        }

        inline void Gamma(PixelColor &color)
        {
            red = gamma8(color.red);
            green = gamma8(color.green);
            blue = gamma8(color.blue);
            white = gamma8(color.white);
        }

        inline void Sine(PixelColor &color)
        {
            red = sine8(color.red);
            green = sine8(color.green);
            blue = sine8(color.blue);
            white = sine8(color.white);
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