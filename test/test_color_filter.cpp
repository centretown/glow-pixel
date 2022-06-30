// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "config.h"
#include "CopyFilter.h"
#include "GammaFilter.h"
#include "SineFilter.h"
#include "BrightnessFilter.h"
#include "PixelMapper.h"

using namespace glow;

void wait(uint32_t ms = 500);

void putFilter(PixelMapper *mapper, PixelColor color, uint32_t ms = 100)
{
    Pixels.Put(mapper, color);
    Pixels.Update();
    wait(ms);
}

void testFilter()
{
    const uint8_t tRed = 0x22;
    const uint8_t tGreen = 0x36;
    const uint8_t tBlue = 0x06;
    const uint8_t tWhite = 0xff;

    PixelColor source, color;
    CopyFilter copyFilter;
    PixelMapper mapper(0, Pixels.Scope()->End());

    TEST_ASSERT_EQUAL_HEX(0, color.Red());
    TEST_ASSERT_EQUAL_HEX(0, color.Green());
    TEST_ASSERT_EQUAL_HEX(0, color.Blue());
    TEST_ASSERT_EQUAL_HEX(0, color.White());

    source.RGBW(tRed, tGreen, tBlue, tWhite);
    TEST_ASSERT_EQUAL_HEX(tRed, source.Red());
    TEST_ASSERT_EQUAL_HEX(tGreen, source.Green());
    TEST_ASSERT_EQUAL_HEX(tBlue, source.Blue());
    TEST_ASSERT_EQUAL_HEX(tWhite, source.White());

    PixelColor &result = copyFilter.Apply(source, color);
    TEST_ASSERT_EQUAL_HEX(tRed, result.Red());
    TEST_ASSERT_EQUAL_HEX(tGreen, result.Green());
    TEST_ASSERT_EQUAL_HEX(tBlue, result.Blue());
    TEST_ASSERT_EQUAL_HEX(tWhite, result.White());

    TEST_ASSERT_EQUAL_HEX(tRed, color.Red());
    TEST_ASSERT_EQUAL_HEX(tGreen, color.Green());
    TEST_ASSERT_EQUAL_HEX(tBlue, color.Blue());
    TEST_ASSERT_EQUAL_HEX(tWhite, color.White());

    GammaFilter gammaFilter;
    gammaFilter.Apply(source, color);
    TEST_ASSERT_EQUAL_HEX(tRed, source.Red());
    TEST_ASSERT_EQUAL_HEX(tGreen, source.Green());
    TEST_ASSERT_EQUAL_HEX(tBlue, source.Blue());
    TEST_ASSERT_EQUAL_HEX(tWhite, source.White());

    TEST_ASSERT_EQUAL_HEX(_basePixel::gamma8(tRed), color.Red());
    TEST_ASSERT_EQUAL_HEX(_basePixel::gamma8(tGreen), color.Green());
    TEST_ASSERT_EQUAL_HEX(_basePixel::gamma8(tBlue), color.Blue());
    TEST_ASSERT_EQUAL_HEX(_basePixel::gamma8(tWhite), color.White());

    SineFilter sineFilter;
    sineFilter.Apply(source, color);
    TEST_ASSERT_EQUAL_HEX(tRed, source.Red());
    TEST_ASSERT_EQUAL_HEX(tGreen, source.Green());
    TEST_ASSERT_EQUAL_HEX(tBlue, source.Blue());
    TEST_ASSERT_EQUAL_HEX(tWhite, source.White());

    TEST_ASSERT_EQUAL_HEX(_basePixel::sine8(tRed), color.Red());
    TEST_ASSERT_EQUAL_HEX(_basePixel::sine8(tGreen), color.Green());
    TEST_ASSERT_EQUAL_HEX(_basePixel::sine8(tBlue), color.Blue());
    TEST_ASSERT_EQUAL_HEX(_basePixel::sine8(tWhite), color.White());

    copyFilter.Link(&gammaFilter);
    copyFilter.Apply(source, color);
    TEST_ASSERT_EQUAL_HEX(_basePixel::gamma8(tRed), color.Red());
    TEST_ASSERT_EQUAL_HEX(_basePixel::gamma8(tGreen), color.Green());
    TEST_ASSERT_EQUAL_HEX(_basePixel::gamma8(tBlue), color.Blue());
    TEST_ASSERT_EQUAL_HEX(_basePixel::gamma8(tWhite), color.White());
    putFilter(&mapper, color);

    copyFilter.Link(&sineFilter);
    copyFilter.Apply(source, color);
    TEST_ASSERT_EQUAL_HEX(_basePixel::sine8(_basePixel::gamma8(tRed)), color.Red());
    TEST_ASSERT_EQUAL_HEX(_basePixel::sine8(_basePixel::gamma8(tGreen)), color.Green());
    TEST_ASSERT_EQUAL_HEX(_basePixel::sine8(_basePixel::gamma8(tBlue)), color.Blue());
    TEST_ASSERT_EQUAL_HEX(_basePixel::sine8(_basePixel::gamma8(tWhite)), color.White());

    gammaFilter.Apply(source, color);
    TEST_ASSERT_EQUAL_HEX(_basePixel::sine8(_basePixel::gamma8(tRed)), color.Red());
    TEST_ASSERT_EQUAL_HEX(_basePixel::sine8(_basePixel::gamma8(tGreen)), color.Green());
    TEST_ASSERT_EQUAL_HEX(_basePixel::sine8(_basePixel::gamma8(tBlue)), color.Blue());
    TEST_ASSERT_EQUAL_HEX(_basePixel::sine8(_basePixel::gamma8(tWhite)), color.White());

    copyFilter.UnLink();
    copyFilter.Apply(source, color);
    TEST_ASSERT_EQUAL_HEX(tRed, color.Red());
    TEST_ASSERT_EQUAL_HEX(tGreen, color.Green());
    TEST_ASSERT_EQUAL_HEX(tBlue, color.Blue());
    TEST_ASSERT_EQUAL_HEX(tWhite, color.White());

    gammaFilter.Apply(source, color);
    TEST_ASSERT_EQUAL_HEX(_basePixel::gamma8(tRed), color.Red());
    TEST_ASSERT_EQUAL_HEX(_basePixel::gamma8(tGreen), color.Green());
    TEST_ASSERT_EQUAL_HEX(_basePixel::gamma8(tBlue), color.Blue());
    TEST_ASSERT_EQUAL_HEX(_basePixel::gamma8(tWhite), color.White());

    sineFilter.Apply(source, color);
    TEST_ASSERT_EQUAL_HEX(_basePixel::sine8(tRed), color.Red());
    TEST_ASSERT_EQUAL_HEX(_basePixel::sine8(tGreen), color.Green());
    TEST_ASSERT_EQUAL_HEX(_basePixel::sine8(tBlue), color.Blue());
    TEST_ASSERT_EQUAL_HEX(_basePixel::sine8(tWhite), color.White());

    copyFilter.Link(&sineFilter);
    copyFilter.Apply(source, color);
    TEST_ASSERT_EQUAL_HEX(_basePixel::sine8(tRed), color.Red());
    TEST_ASSERT_EQUAL_HEX(_basePixel::sine8(tGreen), color.Green());
    TEST_ASSERT_EQUAL_HEX(_basePixel::sine8(tBlue), color.Blue());
    TEST_ASSERT_EQUAL_HEX(_basePixel::sine8(tWhite), color.White());

    copyFilter.UnLink();
    copyFilter.Apply(source, color);
    TEST_ASSERT_EQUAL_HEX(tRed, color.Red());
    TEST_ASSERT_EQUAL_HEX(tGreen, color.Green());
    TEST_ASSERT_EQUAL_HEX(tBlue, color.Blue());
    TEST_ASSERT_EQUAL_HEX(tWhite, color.White());
}

void testBrightnessFilter()
{
    const uint8_t tRed = 0x22;
    const uint8_t tGreen = 0x36;
    const uint8_t tBlue = 0x06;
    const uint8_t tWhite = 0xff;

    BrightnessFilter brightness;
    TEST_ASSERT_EQUAL_HEX(100, brightness.Intensity());

    brightness.Intensity(200);
    TEST_ASSERT_EQUAL_HEX(100, brightness.Intensity());
    brightness.Intensity(100);
    TEST_ASSERT_EQUAL_HEX(100, brightness.Intensity());

    PixelColor source, color;
    source.RGBW(tRed, tGreen, tBlue, tWhite);
    TEST_ASSERT_EQUAL_HEX(tRed, source.Red());
    TEST_ASSERT_EQUAL_HEX(tGreen, source.Green());
    TEST_ASSERT_EQUAL_HEX(tBlue, source.Blue());
    TEST_ASSERT_EQUAL_HEX(tWhite, source.White());

    brightness.Intensity(0);
    brightness.Apply(source, color);
    TEST_ASSERT_EQUAL_HEX(0, color.Red());
    TEST_ASSERT_EQUAL_HEX(0, color.Green());
    TEST_ASSERT_EQUAL_HEX(0, color.Blue());
    TEST_ASSERT_EQUAL_HEX(0, color.White());

    brightness.Intensity(50);
    brightness.Apply(source, color);
    TEST_ASSERT_EQUAL_HEX(tRed / 2, color.Red());
    TEST_ASSERT_EQUAL_HEX(tGreen / 2, color.Green());
    TEST_ASSERT_EQUAL_HEX(tBlue / 2, color.Blue());
    TEST_ASSERT_EQUAL_HEX(tWhite / 2, color.White());

    brightness.Intensity(25);
    brightness.Apply(source, color);
    TEST_ASSERT_EQUAL_HEX(tRed / 4, color.Red());
    TEST_ASSERT_EQUAL_HEX(tGreen / 4, color.Green());
    TEST_ASSERT_EQUAL_HEX(tBlue / 4, color.Blue());
    TEST_ASSERT_EQUAL_HEX(tWhite / 4, color.White());

    brightness.Intensity(10);
    brightness.Apply(source, color);
    TEST_ASSERT_EQUAL_HEX(tRed / 10, color.Red());
    TEST_ASSERT_EQUAL_HEX(tGreen / 10, color.Green());
    TEST_ASSERT_EQUAL_HEX(tBlue / 10, color.Blue());
    TEST_ASSERT_EQUAL_HEX(tWhite / 10, color.White());

    GammaFilter gamma;
    PixelColor testColor;
    testColor.Gamma(color);

    brightness.Link(&gamma);
    brightness.Apply(source, color);

    TEST_ASSERT_EQUAL_HEX(testColor.Red(), color.Red());
    TEST_ASSERT_EQUAL_HEX(testColor.Green(), color.Green());
    TEST_ASSERT_EQUAL_HEX(testColor.Blue(), color.Blue());
    TEST_ASSERT_EQUAL_HEX(testColor.White(), color.White());

    brightness.UnLink();
    brightness.Apply(source, color);
    TEST_ASSERT_EQUAL_HEX(tRed / 10, color.Red());
    TEST_ASSERT_EQUAL_HEX(tGreen / 10, color.Green());
    TEST_ASSERT_EQUAL_HEX(tBlue / 10, color.Blue());
    TEST_ASSERT_EQUAL_HEX(tWhite / 10, color.White());

    brightness.Intensity(50);
    brightness.Apply(source, color);
    testColor.Gamma(color);
    brightness.Apply(testColor, testColor);

    gamma.Link(&brightness);
    gamma.Apply(source, color);
    // TEST_ASSERT_EQUAL_HEX(testColor.Red(), color.Red());
    // TEST_ASSERT_EQUAL_HEX(testColor.Green(), color.Green());
    // TEST_ASSERT_EQUAL_HEX(testColor.Blue(), color.Blue());
    // TEST_ASSERT_EQUAL_HEX(testColor.White(), color.White());
}

void FadeOutFadeIn(PixelColor &source, BrightnessFilter &brightness)
{
    PixelColor color;
    PixelMapper mapper(0, Pixels.Scope()->End());
    for (uint8_t i = 100; i > 0; i--)
    {
        brightness.Intensity(i);
        brightness.Apply(source, color);
        putFilter(&mapper, color, 50);
    }
    for (uint8_t i = 0; i <= 100; i++)
    {
        brightness.Intensity(i);
        brightness.Apply(source, color);
        putFilter(&mapper, color, 50);
    }
}

void testFadeOutFadeIn()
{
    const uint8_t tGreen = 0xff;
    PixelColor source;
    source.GBR(tGreen);
    BrightnessFilter brightness;
    FadeOutFadeIn(source, brightness);
}

void testFadeOutFadeInGamma()
{
    const uint8_t tGreen = 0xff;
    PixelMapper mapper(0, Pixels.Scope()->End());
    PixelColor source;
    source.GBR(tGreen);
    BrightnessFilter brightness;
    GammaFilter gamma;
    brightness.Link(&gamma);
    FadeOutFadeIn(source, brightness);

    source.RGBW(); // clear
    putFilter(&mapper, source);
}

void testFadeOutFadeInSine()
{
    const uint8_t tRed = 0x0f;
    const uint8_t tGreen = 0x3f;
    const uint8_t tBlue = 0x6f;
    PixelColor source;
    source.GBR(tGreen, tBlue, tRed);
    BrightnessFilter brightness;
    SineFilter sine;
    brightness.Link(&sine);
    FadeOutFadeIn(source, brightness);
}

void testColorFilter()
{
    RUN_TEST(testFilter);
    RUN_TEST(testBrightnessFilter);
    RUN_TEST(testFadeOutFadeIn);
    RUN_TEST(testFadeOutFadeInGamma);
    // RUN_TEST(testFadeOutFadeInSine);
}