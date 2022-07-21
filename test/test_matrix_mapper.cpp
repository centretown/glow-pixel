// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>

#include "MatrixMapper.h"
#include "Color.h"
#include "Controller.h"
#include "wait.h"

using color::Color;
using color::color_pack;
using pixel::MatrixMapper;

extern pixel::Controller &Pixels;

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

    Color color(25, 0, 0);
    Range range(Pixels.Scope());
    range <<= 4;
    range.Spin(Pixels, mapper16, color.Pack());
    wait(1000);
}

void testMatrixMappers()
{
    RUN_TEST(testMatrixMapper);
}