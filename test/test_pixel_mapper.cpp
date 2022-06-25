// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>

#include "PixelController.h"
#include "config.h"
#include "OrderedMapper.h"
#include "MatrixMapper.h"

using namespace glow;

void testOrderedMapper()
{
    OrderedMapper mapper(pixelController.PixelCount(), 0);
    TEST_ASSERT_EQUAL(pixelController.PixelCount(), mapper.Length());
    TEST_ASSERT_EQUAL(0, mapper.Get(0));
    TEST_ASSERT_EQUAL(0, mapper.Get(mapper.Length()));
    TEST_ASSERT_EQUAL(2, mapper.Get(2));
    TEST_ASSERT_EQUAL(2, mapper.Get(mapper.Length() + 2));

    OrderedMapper mapperA(pixelController.PixelCount() - 2, 2);
    TEST_ASSERT_EQUAL(pixelController.PixelCount() - 2, mapperA.Length());
    TEST_ASSERT_EQUAL(2, mapperA.Get(0));
    TEST_ASSERT_EQUAL(2, mapperA.Get(mapperA.Length()));
    TEST_ASSERT_EQUAL(4, mapperA.Get(2));
    TEST_ASSERT_EQUAL(4, mapperA.Get(mapperA.Length() + 2));
}

void testMatrixMapper()
{
    uint16_t matrix[4] = {2, 0, 1, 3};
    MatrixMapper mapper(sizeof(matrix), matrix);
}

void testPixelMapper()
{
    RUN_TEST(testOrderedMapper);
    RUN_TEST(testMatrixMapper);
}