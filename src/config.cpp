// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "config.h"

namespace glow
{
#ifdef ARDUINO
#ifdef MEGAATMEGA2560
    static Adafruit_NeoPixel strip19(19, 11, NEO_BRG + NEO_KHZ800);
    static Adafruit_NeoPixel strip15(15, 10, NEO_BRG + NEO_KHZ800);
    static NeoPixelWriter writer(strip19);
    static NeoPixelWriter writer1(strip15);
    PixelWriter *pixelWriters[] = {
        &writer,
        &writer1,
    };
#else

#ifdef ESP32
    static Adafruit_NeoPixel strip8(8, 15, NEO_GRB + NEO_KHZ800);
    static NeoPixelWriter writer(strip8);
    PixelWriter *pixelWriters[] = {
        &writer,
    };
#else
    static Adafruit_NeoPixel strip4(4, 2, NEO_GRB + NEO_KHZ800);
    static NeoPixelWriter writer(strip4);
    PixelWriter *pixelWriters[] = {
        &writer,
    };
#endif // ESP32

#endif // MEGAATMEGA2560

#else
    static NativePixelWriter writer(16);
    PixelWriter *pixelWriters[] = {
        &writer,
    };
#endif // ARDUINO
    size_t pixelWritersCount = sizeof(pixelWriters) / sizeof(pixelWriters[0]);
    PixelController pixelController(pixelWriters, pixelWritersCount);
}