// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>

#include "PixelStrip.h"

// using namespace pixel;


// void writeStrip(PixelStrip &pixel, PixelColor &color, uint32_t ms = 250)
// {
//     for (size_t i = 0; i < pixel.PixelCount(); i++)
//     {
//         pixel.Put(i, color);
//     }
//     pixel.Update();
//     wait(ms);
// }

// void testDimmer()
// {
//     PixelStrip pixel;
//     PixelColor &color = pixel.Color();
//     PixelDimmer &dimmer = pixel.Dimmer();

//     color.BGR(255);
//     auto intensity = dimmer.Intensity();
//     while (intensity > 0)
//     {
//         writeStrip(pixel, 50);
//         intensity--;
//         dimmer.Intensity(intensity);
//     }
//     writeStrip(pixel, 50);

//     color.RGB(255);
//     while (intensity < 100)
//     {
//         writeStrip(pixel, 50);
//         intensity++;
//         dimmer.Intensity(intensity);
//     }
//     writeStrip(pixel, 50);

//     color.GBR(255);
//     while (intensity > 0)
//     {
//         writeStrip(pixel, 50);
//         intensity--;
//         dimmer.Intensity(intensity);
//     }
//     writeStrip(pixel, 50);

//     color.RGB();
//     writeStrip(pixel, 0);
// }

void testStrip()
{
    // PixelStrip pixel;
    // PixelColor &color = pixel.Color();
    // color.GBR(255, 127);
    // writeStrip(pixel);
    // color.BGR(255, 127);
    // writeStrip(pixel);
    // color.RGB(255, 127);
    // writeStrip(pixel);
    // color.RGB(127, 127);
    // writeStrip(pixel);
    // color.RGB();
    // writeStrip(pixel);
}

void testPixelStrip()
{
    RUN_TEST(testStrip);
}
