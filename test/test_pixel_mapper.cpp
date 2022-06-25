// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>

#include "PixelController.h"
#include "SegmentMapper.h"
#include "config.h"

using namespace glow;

void testMapper()
{
    SegmentMapper mapper(0, pixelController.Count());
    TEST_ASSERT_EQUAL(pixelController.Count(), mapper.Length());
    TEST_ASSERT_EQUAL(0, mapper.Minimum());

    SegmentMapper mapperA(2, pixelController.Count()-2);
    TEST_ASSERT_EQUAL(pixelController.Count() - 2, mapperA.Length());
    TEST_ASSERT_EQUAL(2, mapperA.Minimum());
}

void testPixelMapper()
{
    RUN_TEST(testMapper);
}