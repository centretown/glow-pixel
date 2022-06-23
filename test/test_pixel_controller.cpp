// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "PixelController.h"

using namespace glow;

void wait(uint32_t ms = 500);

void writeController(PixelController &controller, PixelColor &color)
{
    for (size_t i = 0; i < controller.Count(); i++)
    {
        controller.Put(i, color);
    }
    controller.Update(0, controller.Count());
    wait();
}

void testPixelController()
{
    PixelController controller(pixelWriters, pixelWritersCount);
    controller.Setup();
    PixelColor color;

    color.GBR(255);
    writeController(controller, color);
    color.BGR(255);
    writeController(controller, color);
    color.RGB(255);
    writeController(controller, color);
    color.RGB(127, 127);
    writeController(controller, color);
    color.RGB();
    writeController(controller, color);
}

void testPixelControllers()
{
    RUN_TEST(testPixelController);
}