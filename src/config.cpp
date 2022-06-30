// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "config.h"

namespace glow
{
#ifdef ARDUINO
#ifdef MEGAATMEGA2560
    // static Adafruit_NeoPixel strip9a(9, 11, NEO_GRB + NEO_KHZ800);
    // static Adafruit_NeoPixel strip9b(9, 10, NEO_GRB + NEO_KHZ800);
    // static Adafruit_NeoPixel strip9c(9, 9, NEO_GRB + NEO_KHZ800);
    // static Adafruit_NeoPixel strip9d(9, 8, NEO_GRB + NEO_KHZ800);
    static Adafruit_NeoPixel strip19(19, 7, NEO_BRG + NEO_KHZ800);
    static Adafruit_NeoPixel strip15(15, 6, NEO_BRG + NEO_KHZ800);

    static NeoPixelDevice device(strip19);
    static NeoPixelDevice device1(strip15);
    // static NeoPixelDevice devicea(strip9a);
    // static NeoPixelDevice deviceb(strip9b);
    // static NeoPixelDevice devicec(strip9c);
    // static NeoPixelDevice deviced(strip9d);
    PixelDevice *pixelDevices[] = {
        // &devicea,
        // &deviced,
        // &devicec,
        // &deviceb,
        &device,
        &device1,
    };
#else

#ifdef ESP32
    static Adafruit_NeoPixel strip9a(9, 27, NEO_GRB + NEO_KHZ800);
    static Adafruit_NeoPixel strip9b(9, 14, NEO_GRB + NEO_KHZ800);
    static Adafruit_NeoPixel strip9c(9, 12, NEO_GRB + NEO_KHZ800);
    static Adafruit_NeoPixel strip9d(9, 13, NEO_GRB + NEO_KHZ800);

    static NeoPixelDevice devicea(strip9a);
    static NeoPixelDevice deviceb(strip9b);
    static NeoPixelDevice devicec(strip9c);
    static NeoPixelDevice deviced(strip9d);

    PixelDevice *pixelDevices[] = {
        &deviced,
        &devicea,
        &deviceb,
        &devicec,
    };
#else  // XIAO
    static Adafruit_NeoPixel strip9a(9, 2, NEO_GRB + NEO_KHZ800);
    static Adafruit_NeoPixel strip9b(9, 3, NEO_GRB + NEO_KHZ800);
    static Adafruit_NeoPixel strip9c(9, 4, NEO_GRB + NEO_KHZ800);
    static Adafruit_NeoPixel strip9d(9, 9, NEO_GRB + NEO_KHZ800);

    static NeoPixelDevice deviceb(strip9b);
    static NeoPixelDevice deviced(strip9d);
    static NeoPixelDevice devicea(strip9a);
    static NeoPixelDevice devicec(strip9c);

    // static Adafruit_NeoPixel strip4(4, 2, NEO_GRB + NEO_KHZ800);
    // static NeoPixelDevice device(strip4);
    PixelDevice *pixelDevices[] = {
        // &device,
        &deviced,
        &deviceb,
        &devicea,
        &devicec,
    };
#endif // ESP32

#endif // MEGAATMEGA2560

#else
    static NativePixelDevice device(16);
    PixelDevice *pixelDevices[] = {
        &device,
    };
#endif // ARDUINO
    static size_t pixelDeviceCount = sizeof(pixelDevices) / sizeof(pixelDevices[0]);
    static PixelController pixelController(pixelDevices, pixelDeviceCount);
    PixelController &Pixels = pixelController;
    size_t PixelDeviceCount() { return pixelDeviceCount; }

}