// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>

#include "Color.h"
#include "Controller.h"
#include "ColorPalette.h"
#include "wait.h"

using color::Color;
using color::color_pack;
using color::ColorPalette;

extern pixel::Controller &Pixels;

void testColorPalette()
{
    const uint8_t tRed = 0x0f;
    const uint8_t tGreen = 0x0f;
    const uint8_t tBlue = 0x0f;

    Color c0(tRed * 3, 0, 0);
    Color c1(tRed, tGreen, 0);
    Color c2(tRed, 0, tBlue);
    Color c3(0, tGreen, 0);
    Color c4(0, tGreen, tBlue);
    Color c5(0, 0, tBlue);
    Color c6(tRed / 2, tGreen / 2, tBlue);
    Color c7(tRed / 2, tGreen, tBlue / 2);
    Color c8(tRed, tGreen / 2, tBlue / 2);

    color_pack palette[] = {
        c0.Pack(),
        c1.Pack(),
        c2.Pack(),
        c3.Pack(),
        c4.Pack(),
        c5.Pack(),
        c6.Pack(),
        c7.Pack(),
        c8.Pack(),
    };

    ColorPalette colorPalette(
        palette,
        sizeof(palette) / sizeof(palette[0]));

    Range range(Pixels.Scope());
    Range(Pixels.Scope()).SpinValues(Pixels, colorPalette);
    wait(1000);

    color_pack palette_a[] = {
        Color(tRed / 2, tGreen / 2, tBlue).Pack(),
        Color(tRed / 2, tGreen, tBlue / 2).Pack(),
        Color(tRed, tGreen / 2, tBlue / 2).Pack(),
    };

    range(36, range.End());
    ColorPalette colorPalette_a(
        palette_a,
        sizeof(palette_a) / sizeof(palette_a[0]));
    range.SpinValues(Pixels, colorPalette_a);
    wait(1000);

    color_pack palette_b[] = {
        0x0f0707,
        0x070f07,
        0x07070f,
    };

    range(36, range.End());
    ColorPalette colorPalette_b(
        palette_b,
        sizeof(palette_b) / sizeof(palette_b[0]));
    range.SpinValues(Pixels, colorPalette_b);
    wait(1000);

}

void testPalettes()
{
    RUN_TEST(testColorPalette);
}