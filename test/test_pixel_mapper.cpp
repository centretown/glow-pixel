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
    SegmentMapper mapper(0, Pixels.PixelCount());
    TEST_ASSERT_EQUAL(Pixels.PixelCount(), mapper.PixelCount());
    TEST_ASSERT_EQUAL(0, mapper.Get(0));
    TEST_ASSERT_EQUAL(0, mapper.Get(mapper.PixelCount()));
    TEST_ASSERT_EQUAL(2, mapper.Get(2));
    TEST_ASSERT_EQUAL(2, mapper.Get(mapper.PixelCount() + 2)); // roll over
    TEST_ASSERT_EQUAL(0, mapper.Begin());
    TEST_ASSERT_EQUAL(Pixels.Scope()->End(), mapper.End());

    SegmentMapper mapperA(2, Pixels.PixelCount() - 2);
    TEST_ASSERT_EQUAL(Pixels.PixelCount() - 2, mapperA.PixelCount());
    TEST_ASSERT_EQUAL(2, mapperA.Get(0));
    TEST_ASSERT_EQUAL(2, mapperA.Get(mapperA.PixelCount()));
    TEST_ASSERT_EQUAL(4, mapperA.Get(2));
    TEST_ASSERT_EQUAL(4, mapperA.Get(mapperA.PixelCount() + 2));
    TEST_ASSERT_EQUAL(2, mapperA.Begin());
    TEST_ASSERT_EQUAL(Pixels.Scope()->End(), mapperA.End());
}

void testMatrix(const uint16_t *matrix, MatrixMapper &mapper)
{
    for (uint16_t i = 0; i < mapper.PixelCount(); i++)
    {
        TEST_ASSERT_EQUAL(matrix[i], mapper.Get(i));
    }
}

static uint16_t matrix16[16] = {
    0x0000, 0x0004, 0x0008, 0x000c, // 0-3
    0x0001, 0x0005, 0x0009, 0x000d, // 4-7
    0x0002, 0x0006, 0x000a, 0x000e, // 8-11
    0x0003, 0x0007, 0x000b, 0x000f, // 12-15
};

// uint16_t matrix12[12] = {
//     0x0000, 0x0004, 0x0008, // 0-
//     0x0001, 0x0005, 0x0009, // 3-5
//     0x0002, 0x0006, 0x000a, // 6-8
//     0x0003, 0x0007, 0x000b, // 10-12
// };

// uint16_t matrix8[8] = {
//     0x0004, 0x0008, // 0-1
//     0x0005, 0x0009, // 2-3
//     0x0006, 0x000a, // 4-5
//     0x0007, 0x000b, // 6-7
// };

void testMatrixMapper()
{
    MatrixMapper mapper16(matrix16, sizeof(matrix16) / sizeof(matrix16[0]));
    testMatrix(matrix16, mapper16);
    TEST_ASSERT_EQUAL(matrix16[3], mapper16.Get(mapper16.PixelCount() + 3));
    TEST_ASSERT_EQUAL(0, mapper16.Begin());
    TEST_ASSERT_EQUAL(0x000f, mapper16.End());
}

void testPixelMapper()
{
    RUN_TEST(testOrderedMapper);
    RUN_TEST(testMatrixMapper);
}