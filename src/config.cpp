// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "config.h"

namespace glow
{
#ifdef ARDUINO
#ifdef MEGAATMEGA2560
    Adafruit_NeoPixel strip19(19, 11, NEO_BRG + NEO_KHZ800);
    Adafruit_NeoPixel strip15(15, 10, NEO_BRG + NEO_KHZ800);
    static NeoPixelWriter writer(strip19);
    static NeoPixelWriter writer1(strip15);
    PixelWriter *pixelWriters[] = {
        &writer,
        &writer1,
    };
    size_t pixelWritersCount = sizeof(pixelWriters) / sizeof(pixelWriters[0]);
#else

#ifdef ESP32
    Adafruit_NeoPixel strip8(8, 15, NEO_GRB + NEO_KHZ800);
    static NeoPixelWriter writer(strip8);
    PixelWriter *pixelWriters[] = {
        &writer,
    };
    size_t pixelWritersCount = sizeof(pixelWriters) / sizeof(pixelWriters[0]);
#else
    Adafruit_NeoPixel strip4(4, 2, NEO_GRB + NEO_KHZ800);
    static NeoPixelWriter writer(strip4);
    PixelWriter *pixelWriters[] = {
        &writer,
    };
    size_t pixelWritersCount = sizeof(pixelWriters) / sizeof(pixelWriters[0]);
#endif // ESP32

#endif // MEGAATMEGA2560

#else
    NativePixelWriter writer;
    PixelWriter *pixelWriters[] = {
        &writer,
    };
    size_t pixelWritersCount = sizeof(pixelWriters) / sizeof(pixelWriters[0]);
#endif // ARDUINO
}