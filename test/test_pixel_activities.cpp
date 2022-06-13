// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "base.h"
#include "config.h"
#include "Activity.h"
#include "PixelGroup.h"
#include "PixelSettings.h"

PixelGroup group(pixelWriters, pixelWritersCount);

void testPixelSolid()
{
}

void testStripActivities()
{
    PixelSettings::Setup(&group);
    RUN_TEST(testPixelSolid);
}