// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "Benchmark.h"

#include "base.h"
#include "wait.h"

#include "Color.h"
#include "Controller.h"

using color::Color;
using color::color_pack;
using pixel::Controller;

extern pixel::Controller &Pixels;

using pixel::Device;
extern pixel::Controller &Pixels;

void SpinDevice(uint16_t index, color_pack color)
{
    Device &device = Pixels.device(index);
    Range range(device.Scope());

    range.Spin(device, color);
    device.Update();
}

void SpinDevices(color_pack color)
{
    for (uint8_t i = 0; i < Pixels.device_count(); i++)
    {
        SpinDevice(i, color);
        wait(500);
    }
}

void testDevices()
{
    SpinDevices(Color(15, 0, 15).Pack());
    SpinDevices(Color(0, 15, 15).Pack());
    SpinDevices(Color(15, 15, 0).Pack());
}

void testPixelDevices()
{
    RUN_TEST(testDevices);
}