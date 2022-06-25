// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>

#include "CopyFilter.h"
#include "GammaFilter.h"
#include "SineFilter.h"

using namespace glow;

void testFilter()
{
    const uint8_t tRed = 0x22;
    const uint8_t tGreen = 0x36;
    const uint8_t tBlue = 0x06;
    const uint8_t tWhite = 0xff;

    PixelColor source, color;
    CopyFilter copyFilter;

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

void testColorFilter()
{
    RUN_TEST(testFilter);
}