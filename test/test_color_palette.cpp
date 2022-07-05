// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>

#include "config.h"
#include "PixelGrid.h"
#include "Putter.h"
#include "SimplePalette.h"

using namespace strip;

void clearPixels();

void putPalette(PixelMapper *mapper,
                ColorPalette *palette,
                uint32_t ms = 100)
{
    TEST_ASSERT(mapper);
    PixelColor backGround(15, 15, 5);
    Pixels.SweepColor(mapper, backGround);
    Pixels.Update();

    PaletteWrap wrapper;
    wrapper.mapper = mapper;
    wrapper.palette = palette;
    wrapper.ms = ms;
    PaletteSweeper sweeper;

    sweeper.Sweep(mapper, &wrapper);

    wait(1000);
    clearPixels();
}

void testSimplePalette()
{
    PixelColor colors[4];
    colors[0].Red(63);
    colors[1].Green(63);
    colors[2].Blue(63);
    colors[3].RGB(21, 21, 21);
    uint16_t length = sizeof(colors) / sizeof(colors[0]);
    SimplePalette palette(colors, length);
    PixelMapper mapper(0, Pixels.Scope()->End());
    putPalette(&mapper, &palette);
}

void testColorPalettes()
{
    RUN_TEST(testSimplePalette);
}