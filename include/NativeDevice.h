// Copyright (c) 2022 Dave Marsh. See LICENSE.
// This file copied part of the Adafruit_NeoPixel.h library.

#ifndef ARDUINO
#pragma once

class NativeDevice
{
private:
    const uint16_t num_pixels;

public:
    NativeDevice(const uint16_t num_pixels)
        : num_pixels(num_pixels) {}

    inline void begin() {}
    inline void clear() {}
    inline void show()
    { //  printf("show\n");
    }
    inline void setPixelColor(uint16_t n, uint8_t r,
                              uint8_t g, uint8_t b)
    {
        // printf("Color:%u-%x:%x:%x\n", n, r, g, b);
    }
    uint16_t numPixels(void) const { return num_pixels; }
};
#endif