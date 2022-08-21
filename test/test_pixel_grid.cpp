// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "Benchmark.h"
#include "wait.h"

#include "Controller.h"
#include "Grid.h"
#include "GradientPalette.h"

extern pixel::Controller &Pixels;

const uint16_t WAIT_TIME = 1000;

using glow::Benchmark;
using pixel::Controller;
using pixel::Grid;
using pixel::GRID_COLUMNS;
using pixel::GRID_ROWS;
using pixel::GRID_ZIGZAG_COLUMNS;
using pixel::GRID_ZIGZAG_ROWS;

using color::GradientPalette;
using color::hue_segment;
using color::hue_size;
using color::luminance_size;
using color::saturation_size;
using color::VARY_HUE;
using color::VARY_LUMINANCE;
using color::VARY_SATURATION;

using color::hue_blue;
using color::hue_cyan;
using color::hue_green;
using color::hue_limit;
using color::hue_magenta;
using color::hue_red;
using color::hue_yellow;

using color::Color;
using color::color_pack;

class TestMapper
{
public:
    Color color;
    Grid &grid;
    uint16_t ms = WAIT_TIME;
    TestMapper(Grid &grid, uint16_t ms = WAIT_TIME)
        : grid(grid), ms(ms) {}

    uint16_t Map(uint16_t index)
    {
        Pixels.Put(grid.Map(index), color(0x00ff00ff));
        wait(ms);
        return grid.Map(index);
    }
};

void showPaletteHues(GradientPalette &palette, Grid &grid)
{
    palette.Vary(VARY_HUE);
    palette(hue_red, hue_limit);
    palette.Fit(grid);
    grid.SpinValues(Pixels, grid, palette);
    wait(WAIT_TIME);

    palette(hue_red, hue_yellow);
    palette.Fit(grid);
    grid.SpinValues(Pixels, grid, palette);
    wait(WAIT_TIME);

    palette(hue_yellow, hue_green);
    palette.Fit(grid);
    grid.SpinValues(Pixels, grid, palette);
    wait(WAIT_TIME);

    palette(hue_green, hue_cyan);
    palette.Fit(grid);
    grid.SpinValues(Pixels, grid, palette);
    wait(WAIT_TIME);

    palette(hue_cyan, hue_blue);
    palette.Fit(grid);
    grid.SpinValues(Pixels, grid, palette);
    wait(WAIT_TIME);

    palette(hue_blue, hue_magenta);
    palette.Fit(grid);
    grid.SpinValues(Pixels, grid, palette);
    wait(WAIT_TIME);

    palette(hue_magenta, hue_limit);
    palette.Fit(grid);
    grid.SpinValues(Pixels, grid, palette);
    wait(WAIT_TIME);

    palette(hue_blue, hue_limit + hue_green);
    palette.Fit(grid);
    grid.SpinValues(Pixels, grid, palette);
    wait(WAIT_TIME);

    palette(hue_blue, hue_limit + hue_green);
    palette.Fit(grid);
    grid.SpinValues(Pixels, grid, palette, true);
    wait(WAIT_TIME);
}

void showPalette(GradientPalette &palette, Grid &grid)
{
    // palette.Fit(grid);
    grid.SpinValues(Pixels, grid, palette, true);
    wait(WAIT_TIME);
}

void testGridGradientPalette()
{
    uint16_t tRows = 4;
    uint16_t tColumns = 9;
    Range range(0, tRows * tColumns);

    GradientPalette palette(VARY_HUE);
    palette.HSL(hue_red, saturation_size, luminance_size / 8);
    Grid grid(range(), tColumns, GRID_ROWS);
    palette.Gamma(true);

    showPaletteHues(palette, grid);
    palette.Reverse(true);
    grid.Rearrange(GRID_COLUMNS);
    showPaletteHues(palette, grid);

    palette.Reverse(false);
    palette.Vary(VARY_SATURATION);
    palette(155, 255);
    palette.HSL(hue_blue, 0, 15);
    palette.Fit(grid);
    showPalette(palette, grid);

    grid.Rearrange(GRID_ROWS);
    palette.Fit(grid);
    showPalette(palette, grid);

    palette.Vary(VARY_LUMINANCE);
    palette(1, luminance_size / 8);
    palette.HSL(hue_green, saturation_size, 0);
    palette.Fit(grid);
    showPalette(palette, grid);

    grid.Rearrange(GRID_ZIGZAG_ROWS);
    palette.Fit(grid);
    grid.SpinValues(Pixels, grid, palette);
    wait(WAIT_TIME);

    grid.Rearrange(GRID_ZIGZAG_COLUMNS);
    palette.Fit(grid);
    grid.SpinValues(Pixels, grid, palette);
    wait(WAIT_TIME);

    palette.Vary(VARY_SATURATION);
    grid.Rearrange(GRID_COLUMNS);
    palette.HSL(hue_blue, saturation_size, 11);
    palette(155, 255);
    palette.Fit(grid);
    grid.SpinValues(Pixels, grid, palette);
    wait(WAIT_TIME);

    palette.Vary(VARY_LUMINANCE);
    grid.Rearrange(GRID_COLUMNS);
    palette.HSL(hue_blue, saturation_size, 0);
    palette(1, 31);
    palette.Fit(grid);
    grid.SpinValues(Pixels, grid, palette);
    wait(WAIT_TIME);

    Range end(Pixels.Scope());
    end(36, end.End());
    grid(end.Pack());
    grid.Rearrange(GRID_ROWS);

    palette(hue_blue, hue_yellow + hue_limit);
    palette.Vary(VARY_HUE);
    palette.HSL(0, saturation_size, 23);
    palette.Fit(grid);
    grid.SpinValues(Pixels, grid, palette);
    wait(WAIT_TIME * 2);

    palette.Vary(VARY_HUE);
    palette.HSL(0, saturation_size, 23);
    palette.Reverse(true);
    grid.SpinValues(Pixels, grid, palette);
    wait(WAIT_TIME);
}

void testGrid()
{
    uint16_t tRows = 4;
    uint16_t tColumns = 9;
    Range range(0, tColumns * tRows);

    Grid grid(range(), tColumns, GRID_ROWS);
    TEST_ASSERT_EQUAL(0, grid.Begin());
    TEST_ASSERT_EQUAL(tRows * tColumns, grid.Length());
    TEST_ASSERT_EQUAL(tRows, grid.Rows());
    TEST_ASSERT_EQUAL(tColumns, grid.Columns());

    uint16_t index = grid.Map(0);
    TEST_ASSERT_EQUAL(grid.Begin(), index);
    index = grid.Map(tColumns);
    TEST_ASSERT_EQUAL(grid.Begin() + tColumns, index);

    grid.Rearrange(GRID_COLUMNS);
    index = grid.Map(0);
    TEST_ASSERT_EQUAL(grid.Begin(), index);
    index = grid.Map(1);
    TEST_ASSERT_EQUAL(grid.Begin() + tColumns, index);
    index = grid.Map(2);
    TEST_ASSERT_EQUAL(grid.Begin() + 2 * tColumns, index);
    index = grid.Map(tRows);
    TEST_ASSERT_EQUAL(grid.Begin() + 1, index);
    index = grid.Map(tRows * 2);
    TEST_ASSERT_EQUAL(grid.Begin() + 2, index);
    index = grid.Map(tRows * 3);
    TEST_ASSERT_EQUAL(grid.Begin() + 3, index);

    grid.Rearrange(GRID_ZIGZAG_COLUMNS);
    index = grid.Map(0);
    TEST_ASSERT_EQUAL(grid.Begin(), index);
    index = grid.Map(1);
    TEST_ASSERT_EQUAL(grid.Begin() + 17, index);
    index = grid.Map(2);
    TEST_ASSERT_EQUAL(grid.Begin() + 18, index);
    index = grid.Map(3);
    TEST_ASSERT_EQUAL(grid.Begin() + 35, index);
    index = grid.Map(4);
    TEST_ASSERT_EQUAL(grid.Begin() + 1, index);
    index = grid.Map(5);
    TEST_ASSERT_EQUAL(grid.Begin() + 16, index);
    index = grid.Map(6);
    TEST_ASSERT_EQUAL(grid.Begin() + 19, index);
    index = grid.Map(7);
    TEST_ASSERT_EQUAL(grid.Begin() + 34, index);
    index = grid.Map(32);
    TEST_ASSERT_EQUAL(grid.Begin() + 8, index);
    index = grid.Map(33);
    TEST_ASSERT_EQUAL(grid.Begin() + 9, index);
    index = grid.Map(34);
    TEST_ASSERT_EQUAL(grid.Begin() + 26, index);
    index = grid.Map(35);
    TEST_ASSERT_EQUAL(grid.Begin() + 27, index);
    index = grid.Map(28);
    TEST_ASSERT_EQUAL(grid.Begin() + 7, index);
    index = grid.Map(31);
    TEST_ASSERT_EQUAL(grid.Begin() + 28, index);

    grid.Rearrange(GRID_ZIGZAG_ROWS);
    index = grid.Map(0);
    TEST_ASSERT_EQUAL(grid.Begin(), index);
    index = grid.Map(1);
    TEST_ASSERT_EQUAL(grid.Begin() + 1, index);
    index = grid.Map(8);
    TEST_ASSERT_EQUAL(grid.Begin() + 8, index);
    index = grid.Map(9);
    TEST_ASSERT_EQUAL(grid.Begin() + 17, index);
    index = grid.Map(10);
    TEST_ASSERT_EQUAL(grid.Begin() + 16, index);
    index = grid.Map(27);
    TEST_ASSERT_EQUAL(grid.Begin() + 35, index);
    index = grid.Map(35);
    TEST_ASSERT_EQUAL(grid.Begin() + 27, index);
}

void testPixelGrids()
{
    RUN_TEST(testGrid);
    RUN_TEST(testGridGradientPalette);
}
