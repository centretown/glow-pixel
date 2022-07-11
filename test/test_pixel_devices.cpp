// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "base.h"
#include "config.h"
#include "Putter.h"

using namespace strip;

void testPixelDevice()
{
    for (size_t i = 0; i < device_count; i++)
    {
        pixelDevices[i]->Setup();
    }

    PixelDevice *device;
    PixelColor color;
    for (size_t i = 0; i < device_count; i++)
    {
        device = pixelDevices[i];
        color.RGB(0xff, 0, 0);
        writeDevice(device, color.Pack());
        color.RGB(0, 0xff, 0);
        writeDevice(device, color.Pack());
        color.RGB(0, 0, 0xff);
        writeDevice(device, color.Pack());
        color.RGB();
        writeDevice(device, color.Pack());
    }
}

void testPixelDevices()
{
    RUN_TEST(testPixelDevice);
}
