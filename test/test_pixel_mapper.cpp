// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>

#include "PixelController.h"
#include "config.h"
#include "PixelMapper.h"
#include "MatrixMapper.h"
#include "Sweeper.h"
#include "Putter.h"

using namespace glow;
using namespace strip;

void clearPixels()
{
    PixelMapper mapper(0, Pixels.PixelCount());
    PixelColor backGround(0, 0, 0);
    Pixels.SweepColor(&mapper, backGround);
    Pixels.Update();
}

void putMapper(PixelMapper *mapper, PixelColor color, uint32_t ms = 100)
{
    TEST_ASSERT(mapper);
    PixelColor backGround(15, 15, 5);
    Pixels.SweepColor(mapper, backGround);
    Pixels.Update();

    ColorWrap puttee;
    puttee.mapper = mapper;
    puttee.color = color;
    puttee.ms = ms;
    ColorPutter putter;

    putter.Sweep(mapper, &puttee);

    wait(1000);
    clearPixels();
}

void testOrderedMapper()
{
    PixelMapper mapper(Pixels.Scope());
    PixelColor color(255);

    TEST_ASSERT_EQUAL(Pixels.PixelCount(), mapper.End());
    TEST_ASSERT_EQUAL(0, mapper.Begin());
    TEST_ASSERT_EQUAL(2, mapper.Get(2));
    TEST_ASSERT_EQUAL(Pixels.Scope()->End(), mapper.End());
    putMapper(&mapper, color);

    PixelMapper mapperA(2, Pixels.PixelCount());
    TEST_ASSERT_EQUAL(2, mapperA.Begin());
    TEST_ASSERT_EQUAL(4, mapperA.Get(4));
    TEST_ASSERT_EQUAL(Pixels.Scope()->End(), mapperA.End());
    color.GBR(255);
    putMapper(&mapperA, color);
}

void testMatrix(const uint16_t *matrix, MatrixMapper &mapper)
{
    for (auto i = mapper.Begin();
         i < mapper.End();
         i++)
    {
        TEST_ASSERT_EQUAL(matrix[i], mapper.Get(i));
    }
}

void testMatrixMapper()
{
    static uint16_t matrix16[16] = {
        0, 9, 18, 27,  //
        1, 10, 19, 28, //
        2, 11, 20, 29, //
        3, 12, 21, 30, //
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

    auto mat16Size = sizeof(matrix16) / sizeof(matrix16[0]);
    MatrixMapper mapper16(matrix16, mat16Size);
    TEST_ASSERT_EQUAL(matrix16[0], mapper16.Begin());
    TEST_ASSERT_EQUAL(matrix16[2], mapper16.Get(2));
    TEST_ASSERT_EQUAL(0, mapper16.Begin());
    TEST_ASSERT_EQUAL(mat16Size, mapper16.End());

    testMatrix(matrix16, mapper16);

    PixelColor color(0, 0, 255);
    putMapper(&mapper16, color);
}

void testPixelMapper()
{
    RUN_TEST(testOrderedMapper);
    RUN_TEST(testMatrixMapper);
}