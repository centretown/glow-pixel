// Copyright (c) 2022 Dave Marsh. See LICENSE.

#pragma once

#include "base.h"

#ifdef ARDUINO
#include <Adafruit_NeoPixel.h>
#else
#include "NativePixel.h"
#endif

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

        inline void RGBW(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t w = 0)
        {
            red = r;
            green = g;
            blue = b;
            white = w;
        }

        inline void Copy(PixelColor &color)
        {
            red = color.red;
            green = color.green;
            blue = color.blue;
            white = color.white;
        }

        inline uint32_t Pack()
        {
#ifdef ARDUINO
            return Adafruit_NeoPixel::Color(red, green, blue, white);
#else
            return NativePixel::Color(red, green, blue, white);
#endif
        }

        inline void UnPack(uint32_t packed)
        {
            uint32_t mask = 0x000000ff;
            blue = packed & mask;
            green = (packed >> 8) & mask;
            red = (packed >> 16) & mask;
            white = (packed >> 24) & mask;
        }

        inline void HSV(uint16_t hue, uint8_t saturation = 255, uint8_t value = 255)
        {
            uint32_t packed = 0;
#ifdef ARDUINO
            packed = Adafruit_NeoPixel::ColorHSV(hue, saturation, value);
#else
            packed = NativePixel::ColorHSV(hue, saturation, value);
#endif
            UnPack(packed);
        }

        inline void Gamma()
        {
            uint32_t packed = 0;
#ifdef ARDUINO
            packed = Adafruit_NeoPixel::gamma32(Pack());
#else
            packed = NativePixel::gamma32(Pack());
#endif
            UnPack(packed);
        }

        static inline uint8_t Sine(uint8_t c)
        {
#ifdef ARDUINO
            return Adafruit_NeoPixel::sine8(c);
#else
            return NativePixel::sine8(c);
#endif
        }
    };
}