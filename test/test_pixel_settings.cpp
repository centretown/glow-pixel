// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>

#include "PixelSettings.h"

using namespace glow;

void wait(uint32_t ms = 500);

void writeSettings(PixelSettings &pixel, uint32_t ms = 500)
{
    for (size_t i = 0; i < pixel.Count(); i++)
    {
        pixel.Put(i);
    }
    pixel.Update();
    wait(ms);
}

void testDimmer()
{
    PixelSettings pixel;
    PixelColor &color = pixel.Color();
    PixelDimmer &dimmer = pixel.Dimmer();

    color.BGR(255);
    auto intensity = dimmer.Intensity();
    while (intensity > 0)
    {
        writeSettings(pixel, 50);
        intensity--;
        dimmer.Intensity(intensity);
    }
    writeSettings(pixel, 50);

    color.RGB(255);
    while (intensity < 100)
    {
        writeSettings(pixel, 50);
        intensity++;
        dimmer.Intensity(intensity);
    }
    writeSettings(pixel, 50);

    color.GBR(255);
    while (intensity > 0)
    {
        writeSettings(pixel, 50);
        intensity--;
        dimmer.Intensity(intensity);
    }
    writeSettings(pixel, 50);

    color.RGB();
    writeSettings(pixel, 0);
}

void testSettings()
{
    PixelSettings pixel;
    PixelColor &color = pixel.Color();
    color.GBR(255, 127);
    writeSettings(pixel);
    color.BGR(255, 127);
    writeSettings(pixel);
    color.RGB(255, 127);
    writeSettings(pixel);
    color.RGB(127, 127);
    writeSettings(pixel);
    color.RGB();
    writeSettings(pixel);
}

void testPixelSettings()
{
    RUN_TEST(testSettings);
    RUN_TEST(testDimmer);
}
