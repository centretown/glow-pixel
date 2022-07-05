// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>

#include "config.h"
#include "PixelGrid.h"
#include "Putter.h"

using namespace strip;

void clearPixels();

void putFrame(PixelGrid *frame, PixelColor color, uint32_t ms = 100)
{
    TEST_ASSERT(frame);
    PixelColor backGround(15, 15, 5);
    Pixels.SweepColor(frame, backGround);
    Pixels.Update();

    ColorWrap puttee;
    puttee.mapper = frame;
    puttee.color = color;
    puttee.ms = ms;
    ColorPutter putter;

    putter.Sweep(frame, &puttee);

    wait(1000);
    clearPixels();
}

void testIndicatorFrame()
{
    PixelColor color;
    SimpleRange rows(0, 1);
    SimpleRange cols(0, 4);
    auto end = Pixels.Scope()->End();
    uint16_t rowLength = 4;
    PixelGrid indicator(end - rowLength, end, rowLength, &rows, &cols);
    auto begin = indicator.Begin();

    indicator.Order(BY_ROW);
    TEST_ASSERT_EQUAL(end - rowLength, indicator.Begin());
    TEST_ASSERT_EQUAL(end, indicator.End());
    TEST_ASSERT_EQUAL(end - rowLength, indicator.Get(begin));
    TEST_ASSERT_EQUAL(begin, indicator.Get(begin));
    TEST_ASSERT_EQUAL(begin + 1, indicator.Get(begin + 1));
    TEST_ASSERT_EQUAL(begin + 2, indicator.Get(begin + 2));
    TEST_ASSERT_EQUAL(begin + 3, indicator.Get(begin + 3));

    color.GBR(127, 127);
    indicator.Order(AS_RANGE);
    putFrame(&indicator, color);

    color.RGB(127, 127);
    indicator.Order(BY_ROW);
    putFrame(&indicator, color);

    rowLength = 5;
    cols.Resize(0, rowLength);
    indicator.Resize(end - rowLength, end, rowLength, &rows, &cols);
    begin = indicator.Begin();
    TEST_ASSERT_EQUAL(5, indicator.Length());
    TEST_ASSERT_EQUAL(end - rowLength, indicator.Get(begin));
    TEST_ASSERT_EQUAL(begin, indicator.Get(begin));
    TEST_ASSERT_EQUAL(begin + 1, indicator.Get(begin + 1));
    TEST_ASSERT_EQUAL(begin + 2, indicator.Get(begin + 2));
    TEST_ASSERT_EQUAL(begin + 3, indicator.Get(begin + 3));

    color.BGR(127, 127);
    indicator.Order(BY_ROW);
    putFrame(&indicator, color);

    color.BGR(127, 0, 127);
    indicator.Order(BY_ROW);
    indicator.Reverse(true);
    putFrame(&indicator, color);
}

void testPixelGrid()
{
    PixelColor color;
    uint16_t rowLength = 9;
    uint16_t colLength = 4;

    SimpleRange rows(0, colLength);
    SimpleRange cols(0, rowLength);
    uint16_t length = rows.Length() * cols.Length();

    PixelGrid grid(0, length, rowLength, &rows, &cols);
    auto begin = grid.Begin();
    auto end = grid.End();
    grid.Order(BY_ROW);
    TEST_ASSERT_EQUAL(end, grid.End());
    TEST_ASSERT_EQUAL(end - length, grid.Get(begin));
    TEST_ASSERT_EQUAL(begin, grid.Get(begin));
    TEST_ASSERT_EQUAL(begin + 1, grid.Get(begin + 1));
    TEST_ASSERT_EQUAL(begin + 2, grid.Get(begin + 2));
    TEST_ASSERT_EQUAL(begin + 3, grid.Get(begin + 3));
    TEST_ASSERT_EQUAL(begin + 8, grid.Get(begin + 8));
    TEST_ASSERT_EQUAL(begin + 9, grid.Get(begin + 9));
    TEST_ASSERT_EQUAL(begin + 10, grid.Get(begin + 10));

    color.BGR(127, 127);
    grid.Order(BY_ROW);
    putFrame(&grid, color);

    color.BGR(195, 95);
    grid.Order(BY_COL);
    putFrame(&grid, color);

    cols.Resize(0, rowLength - 1);
    length = rows.Length() * cols.Length();
    grid.Resize(0, length, rowLength, &rows, &cols);
    color.BGR(127, 127);
    grid.Order(BY_ROW);
    putFrame(&grid, color);

    rows.Resize(0, colLength - 1);
    length = rows.Length() * cols.Length();
    grid.Resize(0, length, rowLength, &rows, &cols);
    color.BGR(195, 95);
    grid.Order(BY_COL);
    putFrame(&grid, color);

    rows.Resize(1, colLength);
    cols.Resize(1, rowLength);
    length = rows.Length() * cols.Length();
    grid.Resize(0, length, rowLength, &rows, &cols);
    grid.Order(BY_ROW);
    color.BGR(95, 195);
    putFrame(&grid, color);

    grid.Reverse(true);
    color.RGB(95, 0, 195);
    putFrame(&grid, color);

    grid.Reverse(false);
    grid.Order(BY_COL);
    color.RGB(95, 195);
    putFrame(&grid, color);

    grid.Reverse(true);
    color.RGB(95, 0, 195);
    putFrame(&grid, color);

    rows.Resize(1, colLength - 1);
    cols.Resize(1, rowLength - 1);
    length = rows.Length() * cols.Length();
    grid.Resize(0, length, rowLength, &rows, &cols);
    grid.Order(BY_ROW);
    color.BGR(95, 195);
    putFrame(&grid, color);

    grid.Reverse(true);
    color.RGB(95, 0, 195);
    putFrame(&grid, color);

    grid.Reverse(false);
    grid.Order(BY_COL);
    color.RGB(95, 195);
    putFrame(&grid, color);

    grid.Reverse(true);
    color.RGB(95, 0, 195);
    putFrame(&grid, color);
}

void testPixelGrids()
{
    RUN_TEST(testIndicatorFrame);
    RUN_TEST(testPixelGrid);
}