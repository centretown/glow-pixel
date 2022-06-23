// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
namespace glow
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

        inline uint8_t Red() { return red; }
        inline void Red(uint8_t r) { red = r; }
        inline uint8_t Green() { return green; }
        inline void Green(uint8_t g) { green = g; }
        inline uint8_t Blue() { return blue; }
        inline void Blue(uint8_t b) { blue = b; }
        inline uint8_t White() { return white; }
        inline void White(uint8_t w) { white = w; }

        inline void RGB(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0)
        {
            RGBW(r, g, b);
        }
        inline void GBR(uint8_t g = 0, uint8_t b = 0, uint8_t r = 0)
        {
            RGBW(r, g, b);
        }
        inline void BGR(uint8_t b = 0, uint8_t r = 0, uint8_t g = 0)
        {
            RGBW(r, g, b);
        }

        inline void WRGB(uint8_t w = 0, uint8_t r = 0, uint8_t g = 0, uint8_t b = 0)
        {
            RGBW(r, g, b, w);
        }

        inline void RGBW(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t w = 0)
        {
            red = r;
            green = g;
            blue = b;
            white = w;
        }
    };
}