// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "PixelController.h"
#include "config.h"
#include "Putter.h"

using namespace strip;

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
    PixelMapper mapper(Pixels.Scope());

    color.RGB(127, 127);
    putController(&mapper, color);
    color.BGR(255);
    putController(&mapper, color);
    color.GBR(255);
    putController(&mapper, color);
    color.RGB(255);
    putController(&mapper, color);
    color.RGB();
    putController(&mapper, color);
}

void testPixelControllers()
{
    RUN_TEST(testPixelController);
    RUN_TEST(testPixelControllerRanges);
}