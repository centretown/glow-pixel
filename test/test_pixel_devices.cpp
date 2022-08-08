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

void testDevicesReadWrite()
{
    uint8_t tRed = 32, tGreen = 55, tBlue = 143;
    Color color(tRed, tGreen, tBlue);
    for (uint8_t i = 0; i < Pixels.device_count(); i++)
    {
        Device &device = Pixels.device(i);
        Range range(device.Scope());
        for (uint16_t j = 0; j < range.Length(); j++)
        {
            device.Put(j, color.Pack());
            color_pack pack = device.Get(j);
            TEST_ASSERT_EQUAL(color.Pack(), pack);
        }
    }
}

void testPixelDevices()
{
    RUN_TEST(testDevices);
    RUN_TEST(testDevicesReadWrite);
}