// Copyright (c) 2022 Dave Marsh. See LICENSE.

#include "config.h"

namespace strip
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
#ifdef ESP32LOCAL
    static Adafruit_NeoPixel strip8a(8, 15, NEO_GRB + NEO_KHZ800); // CH3
    static NeoPixelDevice devicea(strip8a);
    PixelDevice *pixelDevices[] = {
        &devicea,
    };
#else
    static Adafruit_NeoPixel strip9a(9, 27, NEO_GRB + NEO_KHZ800); // CH7
    static Adafruit_NeoPixel strip9b(9, 14, NEO_GRB + NEO_KHZ800); // CH6
    static Adafruit_NeoPixel strip9c(9, 12, NEO_GRB + NEO_KHZ800); // CH5
    static Adafruit_NeoPixel strip9d(9, 13, NEO_GRB + NEO_KHZ800); // CH4
    static Adafruit_NeoPixel strip4e(4, 26, NEO_GRB + NEO_KHZ800); // CH9

    static NeoPixelDevice devicea(strip9a);
    static NeoPixelDevice deviceb(strip9b);
    static NeoPixelDevice devicec(strip9c);
    static NeoPixelDevice deviced(strip9d);
    static NeoPixelDevice devicee(strip4e);

    PixelDevice *pixelDevices[] = {
        &deviced,
        &devicea,
        &deviceb,
        &devicec,
        &devicee,
    };

#endif // ESP32LOCAL
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
    static NativePixelDevice devicea(9);
    static NativePixelDevice deviceb(9);
    static NativePixelDevice devicec(9);
    static NativePixelDevice deviced(9);
    static NativePixelDevice devicee(4);
    PixelDevice *pixelDevices[] = {
        &devicea,
        &deviceb,
        &devicec,
        &deviced,
        &devicee,
    };
#endif // ARDUINO
    static size_t pixelDeviceCount = sizeof(pixelDevices) / sizeof(pixelDevices[0]);
    static PixelController pixelController(pixelDevices, pixelDeviceCount);
    PixelController &Pixels = pixelController;
    size_t PixelDeviceCount() { return pixelDeviceCount; }

}