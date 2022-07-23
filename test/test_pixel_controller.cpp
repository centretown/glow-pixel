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

void testPixelControllers()
{
    RUN_TEST(testPixelController);
}