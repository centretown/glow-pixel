// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "Benchmark.h"
#include "wait.h"

#include "GradientActivity.h"
#include "SlideActivity.h"
#include "Grid.h"

using glow::Benchmark;
using glow::Monitor;
using glow::print_line;

using pixel::GradientActivity;
using pixel::Grid;
using pixel::GRID_COLUMNS;
using pixel::GRID_ROWS;
using pixel::SlideActivity;

using color::Gradient;
using color::GradientPalette;
using color::hue_segment;
using color::hue_size;
using color::luminance_size;
using color::saturation_size;
using color::VARY_HUE;
using color::VARY_HUE_LUMINANCE;
using color::VARY_HUE_SATURATION;
using color::VARY_LUMINANCE;
using color::VARY_SATURATION;

using color::hue_blue;
using color::hue_cyan;
using color::hue_green;
using color::hue_limit;
using color::hue_magenta;
using color::hue_red;
using color::hue_yellow;

void setUp()
{
    Monitor::Cycle();
}

void tearDown() {}

uint32_t testActivity(Activity *activity, uint32_t count = 10)
{
    uint32_t ticks = 0;
    do
    {
        Monitor::Cycle();
        if (activity->Pulse())
        {
            ticks++;
        }
    } while (ticks < count && !activity->Done());

    return ticks;
}

void testGradientActivity()
{
    Benchmark benchmark;
    // set_real_time(true);
    benchmark.Begin("testGradientActivity");

    uint16_t tRows = 4;
    uint16_t tColumns = 9;
    Range range(0, tRows * tColumns);

    GradientPalette palette(
        VARY_HUE, hue_red, saturation_size, luminance_size / 8);
    Gradient &hue = palette.Hue();
    hue(hue_green, hue_blue);
    Grid grid(range(), tColumns, GRID_ROWS);
    palette.Gamma(true);
    palette.Fit(grid);

    GradientActivity activity(palette, grid, 5);
    auto ticks = testActivity(&activity, 1000);
    TEST_ASSERT_EQUAL(ticks, 1000);

    grid.Rearrange(GRID_COLUMNS);
    ticks = testActivity(&activity, 1000);
    TEST_ASSERT_EQUAL(ticks, 1000);

    activity.State(1);
    ticks = testActivity(&activity, 1000);

    activity.State(2);
    ticks = testActivity(&activity, 1000);

    benchmark.End();
    // set_real_time(false);
}

void testSlideActivities()
{
    uint16_t tRows = 4;
    uint16_t tColumns = 9;
    Range range(0, tRows * tColumns);
    Color fill(15, 15, 30);

    GradientPalette palette(
        VARY_HUE, hue_red, saturation_size, 2);
    Gradient &hue = palette.Hue();
    hue(hue_red, hue_yellow);
    Grid grid(range(), tColumns, GRID_ROWS);

    palette.Fit(grid);
    grid.SpinValues(Pixels, palette);

    wait(3000);

    SlideActivity slider(grid, palette, 250);
    auto ticks = testActivity(&slider, 100);
}

void testPixelActivities()
{
    // RUN_TEST(testGradientActivity);
    RUN_TEST(testSlideActivities);
}
