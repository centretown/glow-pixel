// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "config.h"

namespace glow
{
#ifdef ARDUINO
#ifdef MEGAATMEGA2560
    static Adafruit_NeoPixel strip9a(9, 11, NEO_GRB + NEO_KHZ800);
    static Adafruit_NeoPixel strip9b(9, 10, NEO_GRB + NEO_KHZ800);
    static Adafruit_NeoPixel strip9c(9, 9, NEO_GRB + NEO_KHZ800);
    static Adafruit_NeoPixel strip9d(9, 8, NEO_GRB + NEO_KHZ800);
    static Adafruit_NeoPixel strip19(19, 7, NEO_BRG + NEO_KHZ800);
    static Adafruit_NeoPixel strip15(15, 6, NEO_BRG + NEO_KHZ800);

    static NeoPixelDevice device(strip19);
    static NeoPixelDevice device1(strip15);
    static NeoPixelDevice devicea(strip9a);
    static NeoPixelDevice deviceb(strip9b);
    static NeoPixelDevice devicec(strip9c);
    static NeoPixelDevice deviced(strip9d);
    PixelDevice *pixelDevices[] = {
        &device,
        &device1,
        &deviced,
        &deviceb,
        &devicea,
        &devicec,
    };
#else

#ifdef ESP32
    static Adafruit_NeoPixel strip8(8, 15, NEO_GRB + NEO_KHZ800);
    static NeoPixelDevice device(strip8);
    PixelDevice *pixelDevices[] = {
        &device,
    };
#else
    static Adafruit_NeoPixel strip4(4, 2, NEO_GRB + NEO_KHZ800);
    static NeoPixelDevice device(strip4);
    PixelDevice *pixelDevices[] = {
        &device,
    };
#endif // ESP32

#endif // MEGAATMEGA2560

#else
    static NativePixelDevice device(16);
    PixelDevice *pixelDevices[] = {
        &device,
    };
#endif // ARDUINO
    size_t pixelDeviceCount = sizeof(pixelDevices) / sizeof(pixelDevices[0]);
    PixelController pixelController(pixelDevices, pixelDeviceCount);
}