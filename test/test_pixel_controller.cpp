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

void testPixelController()
{
    // PixelController controller(pixelWriters, pixelWritersCount);
    // controller.Setup();
    TEST_ASSERT_GREATER_THAN(0, pixelDeviceCount);
    TEST_ASSERT_GREATER_THAN(0, pixelController.PixelCount());
    PixelColor color;

    color.GBR(255);
    writeController(pixelController, color);
    color.BGR(255);
    writeController(pixelController, color);
    color.RGB(255);
    writeController(pixelController, color);
    color.RGB(127, 127);
    writeController(pixelController, color);
    color.RGB();
    writeController(pixelController, color);
}

void testPixelControllers()
{
    RUN_TEST(testPixelController);
}