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

template <typename PALETTE>
struct PalettePutter
{
    inline void Put(uint16_t index, PALETTE palette)
    {
        Pixels.Put(index, palette.Map(index));
    }

    inline void Update()
    {
        Pixels.Update();
    }
};

void testColorPalette()
{
    const uint8_t tRed = 0x0f;
    const uint8_t tGreen = 0x0f;
    const uint8_t tBlue = 0x0f;
    const uint8_t tWhite = 0x0f;

    Color c0(tRed, 0, 0);
    Color c1(tRed, tGreen, 0);
    Color c2(tRed, tGreen, tBlue);
    Color c3(0, tGreen, tBlue);
    Color c4(tRed, 0, tBlue);
    Color c5(0, 0, tBlue);

    color_pack palette[] = {
        c0.Pack(),
        c1.Pack(),
        c2.Pack(),
        c3.Pack(),
        c4.Pack(),
        c5.Pack(),
    };

    ColorPalette colorPalette(
        palette,
        sizeof(palette) / sizeof(palette[0]));

    PalettePutter<ColorPalette> putter;
    Range range(Pixels.Scope());
    range.Spin(putter, colorPalette);
}

void testPalettes()
{
    RUN_TEST(testColorPalette);
}