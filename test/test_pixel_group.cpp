// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "base.h"
#include "config.h"
#include "PixelGroup.h"

void wait(uint32_t ms = 500);

void writeGroup(PixelGroup &group, uint8_t red, uint8_t green, uint8_t blue)
{
    for (size_t i = 0; i < group.Count(); i++)
    {
        group.Put(i, red, green, blue);
    }
    group.Update(0, group.Count());
    wait();
}

void testPixelGroup()
{
    PixelGroup group(pixelWriters, pixelWritersCount);
    group.Setup();

    writeGroup(group, 0, 255, 0);
    writeGroup(group, 0, 0, 255);
    writeGroup(group, 255, 0, 0);
    writeGroup(group, 255, 255, 255);
    writeGroup(group, 0, 0, 0);
}

void testPixelGroups()
{
    RUN_TEST(testPixelGroup);
}