// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "Controller.h"
#include "config.h"
#include "Putter.h"

using namespace pixel;

void testPixelController()
{
    TEST_ASSERT_GREATER_THAN(0, pixel_count);
    TEST_ASSERT_GREATER_THAN(0, Pixels.PixelCount());

    Controller &ctl = Pixels;
    Color color;
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
    Color color;
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