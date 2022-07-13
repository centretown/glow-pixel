// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>

#include "config.h"
#include "Putter.h"
#include "SimplePalette.h"
#include "ColorHSV.h"

using namespace pixel;

void testSimpleHSVPalette()
{
    // PixelMapper mapper(Pixels.Scope());
    // // mapper.Resize(mapper.Begin(), mapper.End() - 4);

    // const uint16_t color_count = mapper.Length();
    // TEST_ASSERT_GREATER_THAN(0, color_count);
    // color_pack *colors = (color_pack *)malloc(sizeof(color_pack) * color_count);

    // PixelColor color;

    // PixelColorHSV baseHSV;
    // baseHSV.Hue(0x2000);
    // baseHSV.Saturation(0xff);
    // baseHSV.Value(0x3f);

    // size_t counter = 0;
    // uint16_t hue = baseHSV.Hue();
    // uint16_t sat = baseHSV.Saturation();
    // uint16_t val = baseHSV.Value();

    // uint16_t hue_inc = 0xffff / color_count;
    // uint16_t sat_inc = 0xd0 / color_count;
    // uint16_t val_inc = 0x3f / color_count;

    // PixelColorHSV colorHSV(baseHSV.Pack());
    // SimplePalette palette(colors, color_count);

    // auto compare = [&]() -> bool
    // { return (counter < color_count); };

    // // auto put = [&sat, &color, &colorHSV, &counter, &colors]()
    // auto put = [&color, &colorHSV, &counter, &colors]()
    // {
    //     color = colorHSV.ToRGB();
    //     color.Gamma(color);
    //     colors[counter] = color.Pack();
    // };

    // auto incrementSaturation = [&counter, &sat, &sat_inc, &colorHSV]()
    // {
    //     counter++;
    //     sat = colorHSV.Saturation();
    //     sat -= sat_inc;
    //     colorHSV.Saturation(sat);
    // };

    // auto incrementValue = [&counter, &val, &val_inc, &colorHSV]()
    // {
    //     counter++;
    //     val = colorHSV.Value();
    //     val -= val_inc;
    //     colorHSV.Value(val);
    // };

    // auto incrementHue = [&counter, &hue, &hue_inc, &colorHSV]()
    // {
    //     counter++;
    //     hue = colorHSV.Hue();
    //     hue -= hue_inc;
    //     colorHSV.Hue(hue);
    // };

    // auto reset = [&counter, &colorHSV, &baseHSV]()
    // {
    //     counter = 0;
    //     colorHSV.Copy(baseHSV);
    // };

    // Spin(put, compare, incrementValue, reset);
    // putPalette(&mapper, &palette, false, 0);
    // wait(500);
    // Spin(put, compare, incrementHue, reset);
    // putPalette(&mapper, &palette, false, 0);
    // wait(500);
    // Spin(put, compare, incrementSaturation, reset);
    // putPalette(&mapper, &palette, false, 0);

    // free(colors);
}

void testSimplePalette()
{
    Color colors[4];
    colors[0].Red(63);
    colors[1].Green(63);
    colors[2].Blue(63);
    colors[3].RGB(21, 21, 21);
    uint16_t length = sizeof(colors) / sizeof(colors[0]);
    SimplePalette palette((color_pack *)colors, length);
    PixelMapper mapper(Pixels.Scope());
    putPalette(&mapper, &palette, false, 50);
}

void testColorPalettes()
{
    // RUN_TEST(testSimplePalette);
    RUN_TEST(testSimpleHSVPalette);
}