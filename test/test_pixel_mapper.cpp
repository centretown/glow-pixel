// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>

#include "PixelController.h"
#include "config.h"
#include "SegmentMapper.h"
#include "MatrixMapper.h"

using namespace glow;

void testOrderedMapper()
{
    SegmentMapper mapper(0, pixelController.PixelCount());
    TEST_ASSERT_EQUAL(pixelController.PixelCount(), mapper.PixelCount());
    TEST_ASSERT_EQUAL(0, mapper.Get(0));
    TEST_ASSERT_EQUAL(0, mapper.Get(mapper.PixelCount()));
    TEST_ASSERT_EQUAL(2, mapper.Get(2));
    TEST_ASSERT_EQUAL(2, mapper.Get(mapper.PixelCount() + 2));

    SegmentMapper mapperA(2, pixelController.PixelCount() - 2);
    TEST_ASSERT_EQUAL(pixelController.PixelCount() - 2, mapperA.PixelCount());
    TEST_ASSERT_EQUAL(2, mapperA.Get(0));
    TEST_ASSERT_EQUAL(2, mapperA.Get(mapperA.PixelCount()));
    TEST_ASSERT_EQUAL(4, mapperA.Get(2));
    TEST_ASSERT_EQUAL(4, mapperA.Get(mapperA.PixelCount() + 2));
}

void testMatrixMapper()
{
    uint16_t matrix[0x10] = {
        0x0000, 0x0004, 0x0008, 0x000c, // 0-3
        0x0001, 0x0005, 0x0009, 0x000d, // 4-7
        0x0002, 0x0006, 0x000a, 0x000e, // 8-11
        0x0003, 0x0007, 0x000b, 0x000f, // 12-15
    };
    MatrixMapper mapper(matrix, sizeof(matrix));
    for (uint16_t i = 0; i < mapper.PixelCount(); i++)
    {
        TEST_ASSERT_EQUAL(matrix[i], mapper.Get(i));
    }
    TEST_ASSERT_EQUAL_HEX(matrix[3], mapper.Get(mapper.PixelCount() + 3));
}

void testPixelMapper()
{
    RUN_TEST(testOrderedMapper);
    RUN_TEST(testMatrixMapper);
}