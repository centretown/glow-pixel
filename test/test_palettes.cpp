// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>

#include "Color.h"
#include "Controller.h"
#include "ColorPalette.h"
#include "Gradient.h"
#include "GradientPalette.h"
#include "wait.h"

using color::Color;
using color::color_pack;
using color::ColorPalette;
using color::hue_limit;

using color::Gradient;
using color::GradientPalette;
using color::hue_size;
using color::luminance_size;
using color::saturation_size;
using color::VARY_HUE;
using color::VARY_HUE_SATURATION;
using color::VARY_LUMINANCE;
using color::VARY_SATURATION;

using color::hue_blue;
using color::hue_cyan;
using color::hue_green;
using color::hue_limit;
using color::hue_magenta;
using color::hue_red;
using color::hue_yellow;

extern pixel::Controller &Pixels;

const uint16_t WAIT_TIME = 1000;

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
    wait(WAIT_TIME);

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
    wait(WAIT_TIME);

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
    wait(WAIT_TIME);
}

void testHueGradient()
{
    GradientPalette palette(VARY_HUE, 0, 255, 7);
    Gradient &hue = palette.Hue();
    Gradient &saturation = palette.Saturation();
    Gradient &luminance = palette.Luminance();

    TEST_ASSERT_EQUAL(hue_size, hue.Size());
    TEST_ASSERT_EQUAL(saturation_size, saturation.Size());
    TEST_ASSERT_EQUAL(luminance_size, luminance.Size());

    TEST_ASSERT_EQUAL(hue_size, hue.Length());
    TEST_ASSERT_EQUAL(saturation_size, saturation.Length());
    TEST_ASSERT_EQUAL(luminance_size, luminance.Length());

    TEST_ASSERT_EQUAL(VARY_HUE, palette.Vary());

    Color color;
    const uint16_t test_end = 36;
    Range range(0, test_end);
    TEST_ASSERT_EQUAL(test_end, range.Length());
    hue(hue_red, hue_yellow);
    palette.Fit(range);
    TEST_ASSERT_EQUAL(range.Length(), hue.FitLength());
    range.SpinValues(Pixels, palette);
    wait(WAIT_TIME);

    palette.Vary(VARY_SATURATION);
    palette.Gamma(true);
    saturation(155, 255);
    palette(hue_blue, 0, 7);
    palette.Fit(range);
    range.SpinValues(Pixels, palette);
    wait(WAIT_TIME);

    palette.Vary(VARY_HUE_SATURATION);
    palette(hue_blue, 255, 7);
    saturation(155, 255);
    hue(hue_blue, hue_limit + hue_blue);
    palette.Fit(range);
    range.SpinValues(Pixels, palette);
    wait(WAIT_TIME);

    palette.Vary(VARY_LUMINANCE);
    luminance(1, 32);
    palette(hue_blue, 255, 0);
    palette.Fit(range);
    range.SpinValues(Pixels, palette);
    wait(WAIT_TIME);
}

void testLoopHueGradient()
{
    Range range(Pixels.Scope());
    GradientPalette palette(
        VARY_HUE, hue_red, saturation_size, luminance_size / 4);
    palette.Gamma(false);
    Gradient &hue = palette.Hue();

    range(36, range.End());
    hue(hue_green, hue_blue);
    palette.Fit(range);
    range.SpinValues(Pixels, palette);
    wait(WAIT_TIME);

    hue(hue_yellow, hue_magenta);
    palette.Fit(range);
    range.SpinValues(Pixels, palette);
    wait(WAIT_TIME);

    hue(hue_green + 15, hue_magenta - 15);
    palette.Fit(range);
    range.SpinValues(Pixels, palette);
    wait(WAIT_TIME);

    hue(hue_blue, hue_yellow);
    palette.Fit(range);
    range.SpinValues(Pixels, palette);
    wait(WAIT_TIME);

    hue(hue_blue, hue_limit + hue_yellow);
    palette.Fit(range);
    range.SpinValues(Pixels, palette);
    wait(WAIT_TIME);

    hue(hue_cyan, hue_limit + hue_cyan);
    palette.Fit(range);
    range.SpinValues(Pixels, palette);
    wait(WAIT_TIME);

    palette.Vary(VARY_HUE_SATURATION);
    Gradient &saturation = palette.Saturation();
    palette(hue_blue, 255, 15);
    saturation(155, 255);
    hue(hue_blue, hue_limit + hue_blue);
    palette.Fit(range);
    range.SpinValues(Pixels, palette);

    palette.Vary(VARY_LUMINANCE);
    Gradient &luminance = palette.Luminance();
    luminance(1, 32);
    palette(hue_blue, saturation_size, 0);
    palette.Fit(range);
    range.SpinValues(Pixels, palette);
    wait(WAIT_TIME);
}

void testPalettes()
{
    RUN_TEST(testColorPalette);
    RUN_TEST(testHueGradient);
    RUN_TEST(testLoopHueGradient);
}