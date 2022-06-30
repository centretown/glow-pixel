// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "base.h"
#include "config.h"
#include "PixelDevice.h"
using namespace strip;

void wait(uint32_t ms = 500)
{
#ifdef ARDUINO
    delay(ms);
#endif
}

void testColor(PixelDevice *device, PixelColor &color)
{
    uint16_t count = device->PixelCount();
    for (uint16_t i = 0; i < count; i++)
    {
        device->Put(i, color);
    }
    device->Update();
    wait();
}

void testPixelDevice()
{
    for (size_t i = 0; i < PixelDeviceCount(); i++)
    {
        pixelDevices[i]->Setup();
    }

    PixelDevice *device;
    PixelColor color;
    for (size_t i = 0; i < PixelDeviceCount(); i++)
    {
        device = pixelDevices[i];
        color.RGB(0xff, 0, 0);
        testColor(device, color);
        color.RGB(0, 0xff, 0);
        testColor(device, color);
        color.RGB(0, 0, 0xff);
        testColor(device, color);
        color.RGB();
        testColor(device, color);
    }
}

void testPixelDevices()
{
    RUN_TEST(testPixelDevice);
}
