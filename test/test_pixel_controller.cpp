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

void putMapper(PixelMapper *mapper, PixelColor &color)
{
    Pixels.Put(mapper, color);
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
    PixelMapper mapper(0, Pixels.Scope()->End());

    color.RGB(127, 127);
    putMapper(&mapper, color);
    color.BGR(255);
    putMapper(&mapper, color);
    color.GBR(255);
    putMapper(&mapper, color);
    color.RGB(255);
    putMapper(&mapper, color);
    color.RGB();
    putMapper(&mapper, color);
}

void testPixelControllers()
{
    RUN_TEST(testPixelController);
    RUN_TEST(testPixelControllerRanges);
}