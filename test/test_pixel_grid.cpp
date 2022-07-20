// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "Benchmark.h"
#include "wait.h"

#include "config.h"
#include "Controller.h"
#include "GridRows.h"
#include "GridColumns.h"

using glow::Benchmark;
using pixel::Color;
using pixel::color_pack;
using pixel::GridColumns;
using pixel::GridRows;
using pixel::Pixels;

template <typename GRID, uint32_t ms>
class TestMapper
{
public:
    uint16_t Map(uint16_t index)
    {
        wait(ms);
        return index;
        // return GRID.Map(index);
    }
};

void testGrids(range_pack pack, uint16_t columns, uint16_t colLength)
{
    GridColumns colGrid;
    Color color(63, 63, 0);
    Color color1(0, 63, 63);
    Color color2(63, 0, 63);

    // const uint32_t DELAY = 0;
    // auto put = [&]()
    // {
    //     putGrid(&rowGrid, color, color1, false, DELAY);
    //     putGrid(&rowGrid, color, color1, true, DELAY);

    //     colGrid.Copy(&rowGrid);
    //     putGrid(&colGrid, color1, color2, false, DELAY);
    //     putGrid(&colGrid, color1, color2, true, DELAY);
    // };

    // auto reset = [&]()
    // {
    //     rows.Pack(rowsPack);
    //     cols.Pack(colsPack);
    //     rowGrid.Resize(pack, columns, rows.Pack(), cols.Pack());
    // };

    // auto compare = [&]()
    // {
    //     return (cols.Length() > 0 && rows.Length() > 0);
    // };
    // auto increment_row_begin = [&]()
    // {
    //     rows.Resize(rows.Begin() + 1, rows.End());
    //     rowGrid.Resize(pack, columns, rows.Pack(), cols.Pack());
    // };
    // auto decrement_row_end = [&]()
    // {
    //     rows.Resize(rows.Begin(), rows.End() - 1);
    //     rowGrid.Resize(pack, columns, rows.Pack(), cols.Pack());
    // };
    // Spin(compare, put, increment_row_begin, reset);
    // Spin(compare, put, decrement_row_end, reset);

    // auto increment_col_begin = [&]()
    // {
    //     cols.Resize(cols.Begin() + 1, cols.End());
    //     rowGrid.Resize(pack, columns, rows.Pack(), cols.Pack());
    // };
    // auto decrement_col_end = [&]()
    // {
    //     cols.Resize(cols.Begin(), cols.End() - 1);
    //     rowGrid.Resize(pack, columns, rows.Pack(), cols.Pack());
    // };
    // Spin(compare, put, increment_col_begin, reset);
    // Spin(compare, put, decrement_col_end, reset);

    // auto increment_both_begin = [&]()
    // {
    //     rows.Resize(rows.Begin() + 1, rows.End());
    //     cols.Resize(cols.Begin() + 1, cols.End());
    //     rowGrid.Resize(pack, columns, rows.Pack(), cols.Pack());
    // };
    // auto decrement_both_end = [&]()
    // {
    //     rows.Resize(rows.Begin(), rows.End() - 1);
    //     cols.Resize(cols.Begin(), cols.End() - 1);
    //     rowGrid.Resize(pack, columns, rows.Pack(), cols.Pack());
    // };

    // Spin(compare, put, increment_both_begin, reset);
    // Spin(compare, put, decrement_both_end, reset);

    // auto squeeze = [&]()
    // {
    //     rows.Resize(rows.Begin() + 1, rows.End() - 1);
    //     cols.Resize(cols.Begin() + 1, cols.End() - 1);
    //     rowGrid.Resize(pack, columns, rows.Pack(), cols.Pack());
    // };
    // Spin(compare, put, squeeze, reset);
}

void testPixelGrid()
{
    // uint16_t columns = 9;
    // uint16_t colLength = 4;
    // uint16_t length = columns * colLength;
    // Range range(0, length);
    // testGrids(range.Pack(), columns, colLength);
}
void testGridColumns()
{
}

void testGridRows()
{
    // set_real_time(true);
    // Benchmark mark;
    // mark.Begin("testGridRows");

    // uint16_t tRows = 4;
    // uint16_t tColumns = 9;
    // Range range(Pixels.Scope());
    // range -= 4;

    // Range rows(0, tRows);
    // Range cols(0, tColumns);

    // Color color(0, 0, 200);

    // GridRows rowGrid(range(), tColumns, rows(), cols());

    // rowGrid.Spin(Pixels, color());
    // rowGrid.Spin(Pixels, color());

    // mark.End();
    // set_real_time(false);
}

void testPixelGrids()
{
    RUN_TEST(testGridRows);
    RUN_TEST(testGridColumns);
}