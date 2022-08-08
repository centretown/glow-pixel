// Copyright (c) 2022 Dave Marsh. See LICENSE.
// This file copied part of the Adafruit_NeoPixel.h library.

#ifndef ARDUINO
#pragma once
#include "Color.h"
using color::Color;
using color::color_pack;

class NativeDevice
{
private:
    const uint16_t num_pixels;
    uint32_t *pixels;

public:
    NativeDevice(const uint16_t num_pixels)
        : num_pixels(num_pixels)
    {
        pixels = (uint32_t *)malloc(sizeof(uint32_t) * num_pixels);
        memset(pixels, 0, sizeof(uint32_t) * num_pixels);
    }
    ~NativeDevice()
    {
        free(pixels);
    }

    inline void begin() {}
    inline void clear() {}
    inline void show()
    { //  printf("show\n");
    }
    
    inline void setPixelColor(uint16_t index, uint8_t r,
                              uint8_t g, uint8_t b)
    {
        Color color(r, g, b);
        pixels[index] = color.Pack();
    }

    uint32_t getPixelColor(uint16_t index)
    {
        return pixels[index];
    }

    uint16_t numPixels(void) const { return num_pixels; }
};
#endif