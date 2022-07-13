// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"
#include "pixel_base.h"

namespace pixel
{
    typedef uint32_t color_pack;
    typedef struct
    {
        uint8_t blue;
        uint8_t green;
        uint8_t red;
        uint8_t white;
    } color_rgbw;

    class Color
    {
    private:
        union
        {
            color_rgbw rgbw;
            color_pack pack;
        };

    public:
        Color(color_pack pack = 0) : pack(pack) {}

        Color(uint8_t red, uint8_t green,
                   uint8_t blue, uint8_t white = 0)
        {
            RGBW(red, green, blue, white);
        }

        Color(Color &color)
        {
            Pack(color.Pack());
        }

        // access member

        inline uint8_t Red() { return rgbw.red; }
        inline uint8_t Green() { return rgbw.green; }
        inline uint8_t Blue() { return rgbw.blue; }
        inline uint8_t White() { return rgbw.white; }
        inline color_pack Pack() { return pack; }

        // modify member

        inline void Red(uint8_t r) { rgbw.red = r; }
        inline void Green(uint8_t g) { rgbw.green = g; }
        inline void Blue(uint8_t b) { rgbw.blue = b; }
        inline void White(uint8_t w) { rgbw.white = w; }

        // modify all members

        inline void Pack(color_pack v) { pack = v; }

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

        inline void Hue(uint16_t hue, uint8_t saturation = 255, uint8_t value = 255)
        {
            Pack(base_hsv(hue, saturation, value));
        }

        // filter functions (modify all)
        inline void Copy(Color &color)
        {
            Pack(color.Pack());
        }

        inline void Gamma(Color &color)
        {
            rgbw.red = gamma8(color.rgbw.red);
            rgbw.green = gamma8(color.rgbw.green);
            rgbw.blue = gamma8(color.rgbw.blue);
            rgbw.white = gamma8(color.rgbw.white);
        }

        inline void Sine(Color &color)
        {
            rgbw.red = sine8(color.rgbw.red);
            rgbw.green = sine8(color.rgbw.green);
            rgbw.blue = sine8(color.rgbw.blue);
            rgbw.white = sine8(color.rgbw.white);
        }

        inline uint32_t base_pack(uint8_t r, uint8_t g, uint8_t b, uint8_t w)
        {
            return _basePixel::Color(r, g, b, w);
        }

    private:
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
    };
}