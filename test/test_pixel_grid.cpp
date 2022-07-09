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

void testGrids(range_pack pack, uint16_t rowLength, uint16_t colLength)
{
    Range rows(0, colLength);
    Range cols(0, rowLength);

    range_pack rowsPack = rows.Pack();
    range_pack colsPack = cols.Pack();

    PixelRows rowGrid(pack, rowLength, rows.Pack(), cols.Pack());
    PixelColumns colGrid;
    PixelColor color(63, 63, 0);
    PixelColor color1(0, 63, 63);
    PixelColor color2(63, 0, 63);

    const uint32_t DELAY = 0;
    auto put = [&]()
    {
        putGrid(&rowGrid, color, color1, false, DELAY);
        putGrid(&rowGrid, color, color1, true, DELAY);

        colGrid.Copy(&rowGrid);
        putGrid(&colGrid, color1, color2, false, DELAY);
        putGrid(&colGrid, color1, color2, true, DELAY);
    };

    auto reset = [&]()
    {
        rows.Pack(rowsPack);
        cols.Pack(colsPack);
        rowGrid.Resize(pack, rowLength, rows.Pack(), cols.Pack());
    };

    auto compare = [&]()
    {
        return (cols.Length() > 0 && rows.Length() > 0);
    };
    auto increment_row_begin = [&]()
    {
        rows.Resize(rows.Begin() + 1, rows.End());
        rowGrid.Resize(pack, rowLength, rows.Pack(), cols.Pack());
    };
    auto decrement_row_end = [&]()
    {
        rows.Resize(rows.Begin(), rows.End() - 1);
        rowGrid.Resize(pack, rowLength, rows.Pack(), cols.Pack());
    };
    Looper(compare, put, increment_row_begin, reset);
    Looper(compare, put, decrement_row_end, reset);

    auto increment_col_begin = [&]()
    {
        cols.Resize(cols.Begin() + 1, cols.End());
        rowGrid.Resize(pack, rowLength, rows.Pack(), cols.Pack());
    };
    auto decrement_col_end = [&]()
    {
        cols.Resize(cols.Begin(), cols.End() - 1);
        rowGrid.Resize(pack, rowLength, rows.Pack(), cols.Pack());
    };
    Looper(compare, put, increment_col_begin, reset);
    Looper(compare, put, decrement_col_end, reset);

    auto increment_both_begin = [&]()
    {
        rows.Resize(rows.Begin() + 1, rows.End());
        cols.Resize(cols.Begin() + 1, cols.End());
        rowGrid.Resize(pack, rowLength, rows.Pack(), cols.Pack());
    };
    auto decrement_both_end = [&]()
    {
        rows.Resize(rows.Begin(), rows.End() - 1);
        cols.Resize(cols.Begin(), cols.End() - 1);
        rowGrid.Resize(pack, rowLength, rows.Pack(), cols.Pack());
    };

    Looper(compare, put, increment_both_begin, reset);
    Looper(compare, put, decrement_both_end, reset);

    auto squeeze = [&]()
    {
        rows.Resize(rows.Begin() + 1, rows.End() - 1);
        cols.Resize(cols.Begin() + 1, cols.End() - 1);
        rowGrid.Resize(pack, rowLength, rows.Pack(), cols.Pack());
    };
    Looper(compare, put, squeeze, reset);
}

void testPixelGrid()
{
    uint16_t rowLength = 9;
    uint16_t colLength = 4;
    uint16_t length = rowLength * colLength;
    Range range(0, length);
    testGrids(range.Pack(), rowLength, colLength);
}

void testPixelGrids()
{
    RUN_TEST(testIndicatorFrame);
    RUN_TEST(testPixelGrid);
}