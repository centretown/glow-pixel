// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>

#include "PixelColor.h"

using namespace strip;

void testColor()
{
    const uint8_t tRed = 0xef;
    const uint8_t tGreen = 0x43;
    const uint8_t tBlue = 0x21;
    const uint8_t tWhite = 0x99;
    PixelColor color;
    TEST_ASSERT_EQUAL(0, color.Red());
    TEST_ASSERT_EQUAL(0, color.Green());
    TEST_ASSERT_EQUAL(0, color.Blue());
    TEST_ASSERT_EQUAL(0, color.White());

    color.Red(tRed);
    TEST_ASSERT_EQUAL(tRed, color.Red());
    color.Green(tGreen);
    TEST_ASSERT_EQUAL(tGreen, color.Green());
    color.Blue(tBlue);
    TEST_ASSERT_EQUAL(tBlue, color.Blue());
    color.White(tWhite);
    TEST_ASSERT_EQUAL(tWhite, color.White());

    // uint32_t packed = color.Pack();
    uint32_t packed = color.base_pack(tRed, tGreen, tBlue, tWhite);
    uint32_t expected = (uint32_t)tWhite << 24;
    expected |= (uint32_t)tRed << 16;
    expected |= (uint32_t)tGreen << 8;
    expected |= (uint32_t)tBlue;
    TEST_ASSERT_EQUAL(expected, packed);
    TEST_ASSERT_EQUAL(expected, color.Pack());

    TEST_ASSERT_EQUAL(tRed, color.Red());
    TEST_ASSERT_EQUAL(tGreen, color.Green());
    TEST_ASSERT_EQUAL(tBlue, color.Blue());
    TEST_ASSERT_EQUAL(tWhite, color.White());

    PixelColor other(color);
    TEST_ASSERT_EQUAL(tRed, other.Red());
    TEST_ASSERT_EQUAL(tGreen, other.Green());
    TEST_ASSERT_EQUAL(tBlue, other.Blue());
    TEST_ASSERT_EQUAL(tWhite, other.White());

    other.Pack(packed);
    TEST_ASSERT_EQUAL(tRed, other.Red());
    TEST_ASSERT_EQUAL(tGreen, other.Green());
    TEST_ASSERT_EQUAL(tBlue, other.Blue());
    TEST_ASSERT_EQUAL(tWhite, other.White());

    other.RGB();
    TEST_ASSERT_EQUAL(0, other.Red());
    TEST_ASSERT_EQUAL(0, other.Green());
    TEST_ASSERT_EQUAL(0, other.Blue());
    TEST_ASSERT_EQUAL(0, other.White());

    other.Copy(color);
    TEST_ASSERT_EQUAL(tRed, other.Red());
    TEST_ASSERT_EQUAL(tGreen, other.Green());
    TEST_ASSERT_EQUAL(tBlue, other.Blue());
    TEST_ASSERT_EQUAL(tWhite, other.White());

    other.Gamma(color);
    TEST_ASSERT_EQUAL(_basePixel::gamma8(tRed), other.Red());
    TEST_ASSERT_EQUAL(_basePixel::gamma8(tGreen), other.Green());
    TEST_ASSERT_EQUAL(_basePixel::gamma8(tBlue), other.Blue());
    TEST_ASSERT_EQUAL(_basePixel::gamma8(tWhite), other.White());

    TEST_ASSERT_EQUAL(tRed, color.Red());
    TEST_ASSERT_EQUAL(tGreen, color.Green());
    TEST_ASSERT_EQUAL(tBlue, color.Blue());
    TEST_ASSERT_EQUAL(tWhite, color.White());

    other.Sine(color);
    TEST_ASSERT_EQUAL(_basePixel::sine8(tRed), other.Red());
    TEST_ASSERT_EQUAL(_basePixel::sine8(tGreen), other.Green());
    TEST_ASSERT_EQUAL(_basePixel::sine8(tBlue), other.Blue());
    TEST_ASSERT_EQUAL(_basePixel::sine8(tWhite), other.White());

    other.Copy(color);
    other.Hue(0);
    TEST_ASSERT_EQUAL(255, other.Red());
    TEST_ASSERT_EQUAL(0, other.Green());
    TEST_ASSERT_EQUAL(0, other.Blue());
    TEST_ASSERT_EQUAL(0, other.White());
    TEST_ASSERT_NOT_EQUAL(tRed, other.Red());
    TEST_ASSERT_NOT_EQUAL(tGreen, other.Green());
    TEST_ASSERT_NOT_EQUAL(tBlue, other.Blue());

    other.RGBW();
    TEST_ASSERT_EQUAL(0, other.Red());
    TEST_ASSERT_EQUAL(0, other.Green());
    TEST_ASSERT_EQUAL(0, other.Blue());
    TEST_ASSERT_EQUAL(0, other.White());

    other.RGBW(tRed, tGreen, tBlue, tWhite);
    TEST_ASSERT_EQUAL(tRed, other.Red());
    TEST_ASSERT_EQUAL(tGreen, other.Green());
    TEST_ASSERT_EQUAL(tBlue, other.Blue());
    TEST_ASSERT_EQUAL(tWhite, other.White());

    other.RGB();
    TEST_ASSERT_EQUAL(0, other.Red());
    TEST_ASSERT_EQUAL(0, other.Green());
    TEST_ASSERT_EQUAL(0, other.Blue());
    TEST_ASSERT_EQUAL(0, other.White());

    other.RGB(tRed);
    TEST_ASSERT_EQUAL(tRed, other.Red());
    TEST_ASSERT_EQUAL(0, other.Green());
    TEST_ASSERT_EQUAL(0, other.Blue());
    TEST_ASSERT_EQUAL(0, other.White());

    other.GBR(tGreen, tBlue);
    TEST_ASSERT_EQUAL(0, other.Red());
    TEST_ASSERT_EQUAL(tGreen, other.Green());
    TEST_ASSERT_EQUAL(tBlue, other.Blue());
    TEST_ASSERT_EQUAL(0, other.White());

    color.RGBW(tRed, tGreen, tBlue, tWhite);
    packed = color.base_pack(tRed, tGreen, tBlue, tWhite);
    TEST_ASSERT_EQUAL_HEX32(packed, color.Pack());
}

void testPixelColor()
{
    RUN_TEST(testColor);
}