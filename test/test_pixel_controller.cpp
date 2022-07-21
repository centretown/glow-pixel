// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>

#include "Color.h"
#include "Controller.h"

using color::Color;
using pixel::Controller;

extern pixel::Controller& Pixels;


void testPixelController()
{
    TEST_ASSERT_GREATER_THAN(0, Pixels.PixelCount());

    Range range(Pixels.Scope());

    Color color;
    color.GBR(15);
    range.Spin(Pixels, color.Pack());
}

void testPixelControllers()
{
    RUN_TEST(testPixelController);
}