// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>

#include "config.h"
#include "PixelRows.h"
#include "PixelColumns.h"
#include "Putter.h"

using namespace strip;

void testIndicatorFrame()
{
    PixelColor color;
    Range rows(0, 1);
    Range cols(0, 4);
    Range range(Pixels.Scope());
    range.Resize(range.End() - 4, range.End());

    auto end = range.End();
    uint16_t rowLength = 4;
    PixelRows indicator(range.Pack(), rowLength, rows.Pack(), cols.Pack());
    auto begin = indicator.Begin();

    TEST_ASSERT_EQUAL(end - rowLength, indicator.Begin());
    TEST_ASSERT_EQUAL(end, indicator.End());
    TEST_ASSERT_EQUAL(end - rowLength, indicator.Get(begin));
    TEST_ASSERT_EQUAL(begin, indicator.Get(begin));
    TEST_ASSERT_EQUAL(begin + 1, indicator.Get(begin + 1));
    TEST_ASSERT_EQUAL(begin + 2, indicator.Get(begin + 2));
    TEST_ASSERT_EQUAL(begin + 3, indicator.Get(begin + 3));

    color.RGB(127, 127);
    putMapper(&indicator, color);

    rowLength = 5;
    cols.Resize(0, rowLength);
    range.Resize(range.Begin() - 1, range.End());
    indicator.Resize(range.Pack(), rowLength, rows.Pack(), cols.Pack());
    begin = indicator.Begin();
    TEST_ASSERT_EQUAL(5, indicator.Length());
    TEST_ASSERT_EQUAL(end - rowLength, indicator.Get(begin));
    TEST_ASSERT_EQUAL(begin, indicator.Get(begin));
    TEST_ASSERT_EQUAL(begin + 1, indicator.Get(begin + 1));
    TEST_ASSERT_EQUAL(begin + 2, indicator.Get(begin + 2));
    TEST_ASSERT_EQUAL(begin + 3, indicator.Get(begin + 3));
    color.GBR(127, 127);
    putMapper(&indicator, color);
}

void testPixelGrid()
{
    PixelColor color;
    uint16_t rowLength = 9;
    uint16_t colLength = 4;

    Range rows(0, colLength);
    Range cols(0, rowLength);
    uint16_t length = rows.Length() * cols.Length();
    Range range(0, length);

    PixelRows rowGrid(range.Pack(), rowLength,
                   rows.Pack(), cols.Pack());
    auto begin = rowGrid.Begin();
    auto end = rowGrid.End();
    TEST_ASSERT_EQUAL(end, rowGrid.End());
    TEST_ASSERT_EQUAL(end - length, rowGrid.Get(begin));
    TEST_ASSERT_EQUAL(begin, rowGrid.Get(begin));
    TEST_ASSERT_EQUAL(begin + 1, rowGrid.Get(begin + 1));
    TEST_ASSERT_EQUAL(begin + 2, rowGrid.Get(begin + 2));
    TEST_ASSERT_EQUAL(begin + 3, rowGrid.Get(begin + 3));
    TEST_ASSERT_EQUAL(begin + 8, rowGrid.Get(begin + 8));
    TEST_ASSERT_EQUAL(begin + 9, rowGrid.Get(begin + 9));
    TEST_ASSERT_EQUAL(begin + 10, rowGrid.Get(begin + 10));
    color.BGR(127, 127);
    putMapper(&rowGrid, color);

    PixelColumns colGrid(range.Pack(), rowLength,
                   rows.Pack(), cols.Pack());
    TEST_ASSERT_EQUAL(end, colGrid.End());
    TEST_ASSERT_EQUAL(end - length, rowGrid.Get(begin));
    TEST_ASSERT_EQUAL(begin, colGrid.Get(begin));
    // TEST_ASSERT_EQUAL(begin + 1, colGrid.Get(begin + 1));
    // TEST_ASSERT_EQUAL(begin + 2, colGrid.Get(begin + 2));
    // TEST_ASSERT_EQUAL(begin + 3, colGrid.Get(begin + 3));
    // TEST_ASSERT_EQUAL(begin + 8, colGrid.Get(begin + 8));
    // TEST_ASSERT_EQUAL(begin + 9, colGrid.Get(begin + 9));
    // TEST_ASSERT_EQUAL(begin + 10, colGrid.Get(begin + 10));

    color.BGR(195, 95);
    putMapper(&colGrid, color);

    // cols.Resize(0, rowLength - 1);
    // length = rows.Length() * cols.Length();
    // rowGrid.Resize(0, length, rowLength, &rows, &cols);
    // color.BGR(127, 127);
    // rowGrid.Order(BY_ROW);
    // putMapper(&rowGrid, color);

    // rows.Resize(0, colLength - 1);
    // length = rows.Length() * cols.Length();
    // rowGrid.Resize(0, length, rowLength, &rows, &cols);
    // color.BGR(195, 95);
    // rowGrid.Order(BY_COL);
    // putMapper(&rowGrid, color);

    // rows.Resize(1, colLength);
    // cols.Resize(1, rowLength);
    // length = rows.Length() * cols.Length();
    // rowGrid.Resize(0, length, rowLength, &rows, &cols);
    // rowGrid.Order(BY_ROW);
    // color.BGR(95, 195);
    // putMapper(&rowGrid, color);

    // rowGrid.Reverse(true);
    // color.RGB(95, 0, 195);
    // putMapper(&rowGrid, color);

    // rowGrid.Reverse(false);
    // rowGrid.Order(BY_COL);
    // color.RGB(95, 195);
    // putMapper(&rowGrid, color);

    // rowGrid.Reverse(true);
    // color.RGB(95, 0, 195);
    // putMapper(&rowGrid, color);

    // rows.Resize(1, colLength - 1);
    // cols.Resize(1, rowLength - 1);
    // length = rows.Length() * cols.Length();
    // rowGrid.Resize(0, length, rowLength, &rows, &cols);
    // rowGrid.Order(BY_ROW);
    // color.BGR(95, 195);
    // putMapper(&rowGrid, color);

    // rowGrid.Reverse(true);
    // color.RGB(95, 0, 195);
    // putMapper(&rowGrid, color);

    // rowGrid.Reverse(false);
    // rowGrid.Order(BY_COL);
    // color.RGB(95, 195);
    // putMapper(&rowGrid, color);

    // rowGrid.Reverse(true);
    // color.RGB(95, 0, 195);
    // putMapper(&rowGrid, color);
}

void testPixelGrids()
{
    RUN_TEST(testIndicatorFrame);
    RUN_TEST(testPixelGrid);
}