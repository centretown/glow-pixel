// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>

#include "config.h"
#include "PixelGrid.h"
#include "Putter.h"
#include "SimplePalette.h"

using namespace strip;

void testSimplePalette()
{
    PixelColor colors[4];
    colors[0].Red(63);
    colors[1].Green(63);
    colors[2].Blue(63);
    colors[3].RGB(21, 21, 21);
    uint16_t length = sizeof(colors) / sizeof(colors[0]);
    SimplePalette palette((color_pack *)colors, length);
    PixelMapper mapper(Pixels.Scope());
    putPalette(&mapper, &palette);
}

void testColorPalettes()
{
    RUN_TEST(testSimplePalette);
}