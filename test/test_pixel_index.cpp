// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "PixelIndex.h"
#include "Putter.h"

using namespace pixel;

void testPixelIndex()
{
    Device *devices = pixelDevices;
    TEST_ASSERT_NOT_NULL(devices);
    const uint8_t deviceCount = device_count;
    TEST_ASSERT_GREATER_THAN(0, deviceCount);

    uint16_t partitions[deviceCount + 1] = {0};

    uint16_t pixelCount = 0;
    partitions[0] = 0;
    for (uint8_t i = 0; i < deviceCount; i++)
    {
        pixelCount += devices[i].PixelCount();
        partitions[i + 1] = pixelCount;
    }

    // //////////////////////////////////////
    pixel_index index[pixel_count];

    uint8_t deviceIndex = 0;

    for (uint16_t i = 0; i < pixelCount; i++)
    {
        for (deviceIndex = 0;
             partitions[deviceIndex + 1] <= i;
             deviceIndex++)
            ;
        index[i].offset = i - partitions[deviceIndex];
        index[i].device = deviceIndex;
    }

    for (uint16_t i = 0; i < pixelCount; i++)
    {
        for (deviceIndex = 0;
             partitions[deviceIndex + 1] <= i;
             deviceIndex++)
            ;
        TEST_ASSERT_EQUAL(deviceIndex, index[i].device);
        TEST_ASSERT_EQUAL(i - partitions[deviceIndex],
                          index[i].offset);
        TEST_ASSERT_EQUAL(index[i].device, pixelIndex[i].device);
        TEST_ASSERT_EQUAL(index[i].offset, pixelIndex[i].offset);
    }

    Color color(0, 0, 0x80);
    for (size_t i = 0; i < pixelCount; i++)
    {
        writeDevicePixel(&devices[index[i].device],
                         index[i].offset, color.Pack(), 200);
    }

    // //////////////////////////////////////
    // free(index);
}

void testPixelIndeces()
{
    RUN_TEST(testPixelIndex);
}
