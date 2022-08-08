// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>

#include "Color.h"
#include "Controller.h"
#include "wait.h"

using color::Color;
using pixel::Controller;

extern pixel::Controller &Pixels;

void testPixelController()
{
    TEST_ASSERT_GREATER_THAN(0, Pixels.PixelCount());

    Range range(Pixels.Scope());

    Color color(15, 0, 15);
    range.Spin(Pixels, color.Pack());
    wait(1000);

    color(0, 15, 15);
    range.Spin(Pixels, color.Pack());
    wait(1000);
}

void testControllerReadWrite()
{
    uint8_t tRed = 32, tGreen = 55, tBlue = 143;
    Color color(tRed, tGreen, tBlue);
    Range range(Pixels.Scope());

    for (uint16_t j = 0; j < range.Length(); j++)
    {
        Pixels.Put(j, color.Pack());
        color_pack pack = Pixels.Get(j);
        TEST_ASSERT_EQUAL(color.Pack(), pack);
    }
}

void testPixelControllers()
{
    RUN_TEST(testPixelController);
    RUN_TEST(testControllerReadWrite);
}