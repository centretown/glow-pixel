// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "PixelController.h"
#include "config.h"

using namespace glow;

void wait(uint32_t ms = 500);

void writeController(PixelController &controller, PixelColor &color)
{
    for (size_t i = 0; i < controller.PixelCount(); i++)
    {
        controller.Put(i, color);
    }
    controller.Update();
    wait();
}

void putRange(PixelColor &color)
{
    Pixels.Put(Pixels.Domain(), color);
    Pixels.Update();
    wait();
}

void testPixelController()
{
    TEST_ASSERT_GREATER_THAN(0, PixelDeviceCount());
    TEST_ASSERT_GREATER_THAN(0, Pixels.PixelCount());

    PixelController &ctl = Pixels;
    PixelColor color;
    color.GBR(255);
    writeController(ctl, color);
    color.BGR(255);
    writeController(ctl, color);
    color.RGB(255);
    writeController(ctl, color);
    color.RGB(127, 127);
    writeController(ctl, color);
    color.RGB();
    writeController(ctl, color);
}

void testPixelControllerRanges()
{
    PixelColor color;

    color.RGB(127, 127);
    putRange(color);
    color.BGR(255);
    putRange(color);
    color.GBR(255);
    putRange(color);
    color.RGB(255);
    putRange(color);
    color.RGB();
    putRange(color);
}

void testPixelControllers()
{
    RUN_TEST(testPixelController);
    RUN_TEST(testPixelControllerRanges);
}