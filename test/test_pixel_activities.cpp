// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

#include <unity.h>
#include "Benchmark.h"
#include "wait.h"

#include "Activity.h"
#include "HueUpdater.h"
#include "LuminanceUpdater.h"
#include "SaturationUpdater.h"
#include "GradientUpdater.h"
// #include "SlideActivity.h"
#include "Grid.h"
#include "StateHandler.h"

#ifdef ARDUINO

#include "RotaryUpdater.h"
using glow::StateHandler;

using glowui::RotaryUpdater;

#endif

using glow::Activity;
using glow::Benchmark;
using glow::Monitor;
using glow::print_line;

using pixel::GradientUpdater;
using pixel::Grid;
using pixel::GRID_COLUMNS;
using pixel::GRID_ROWS;
using pixel::HueUpdater;
using pixel::LuminanceUpdater;
using pixel::SaturationUpdater;
// using pixel::SlideActivity;

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

void setUp()
{
    Monitor::Cycle();
}

void tearDown() {}

// uint32_t testActivity(Activity &activity, uint32_t count = 10)
// {
//     uint32_t ticks = 0;
//     do
//     {
//         Monitor::Cycle();
//         if (activity.Pulse())
//         {
//             ticks++;
//         }
//     } while (ticks < count && !activity.Done());

//     return ticks;
// }

// void testHueGradientActivity()
// {
//     Benchmark benchmark;
//     // set_real_time(true);
//     benchmark.Begin("testGradientActivity");

//     uint16_t tRows = 4;
//     uint16_t tColumns = 9;
//     Range range(0, tRows * tColumns);
//     Grid grid(range(), tColumns, GRID_ROWS);

//     GradientPalette palette(VARY_HUE);
//     palette.HSL(hue_red, saturation_size, luminance_size / 8);
//     palette(hue_green, hue_blue + hue_limit);
//     palette.Gamma(true);
//     palette.Fit(grid);

//     HueUpdater updater(grid, palette, 20);
//     Activity activity(&updater);
//     palette(hue_green + 127, hue_blue - 127);
//     auto pw = updater.Update();
//     TEST_ASSERT_EQUAL(pw, 20);

//     auto ticks = testActivity(activity, 1000);
//     TEST_ASSERT_EQUAL(ticks, 1000);

//     LuminanceUpdater updaterL(grid, palette, 20);
//     Activity activityL(&updaterL);
//     palette(1, 31);
//     palette.Fit(grid);
//     palette.HSL(hue_yellow, saturation_size, 0);
//     updaterL.Update();
//     ticks = testActivity(activityL, 1000);
//     TEST_ASSERT_EQUAL(ticks, 1000);

//     SaturationUpdater updaterS(grid, palette, 20);
//     Activity activityS(&updaterS);
//     palette(saturation_size / 2, saturation_size);
//     palette.Fit(grid);
//     updaterS.Update();
//     ticks = testActivity(activityS, 1000);
//     TEST_ASSERT_EQUAL(ticks, 1000);

//     benchmark.End();
//     // set_real_time(false);
// }

#ifdef ARDUINO

void testLoop(Activity &source, Activity &target,
              uint32_t count = 5000, uint32_t ms = 10)
{
    StateHandler handler;

    for (uint32_t i = 0; i < count; i++)
    {
        Monitor::Cycle();
        source.Pulse();
        target.Pulse();
        wait(1);
    }
}

const uint8_t encoderA = 21;
const uint8_t encoderB = 5;
const uint8_t button = 15;

void testRotaryLuminance()
{
    char buffer[32];
    uint16_t tRows = 4;
    uint16_t tColumns = 9;
    Range range(0, tRows * tColumns);
    Grid grid(range(), tColumns, GRID_ROWS);

    GradientPalette palette(VARY_HUE);
    palette.HSL(hue_red, saturation_size, luminance_size / 8);
    palette(hue_green, hue_blue + hue_limit);
    palette.Gamma(true);
    palette.Fit(grid);

    HueUpdater hueUpdater(grid, palette, 20);
    Activity hueActivity(&hueUpdater);
    palette(hue_red, hue_blue);
    hueUpdater.Update();
    snprintf(buffer, sizeof(buffer), "hueUpdater...\n");
    print_line(buffer);
    wait(1000);

    RotaryUpdater rotary(encoderA, encoderB, button, true);
    Activity rotaryActivity(&rotary, &hueUpdater);
    rotaryActivity.PulseWidth(2);
    snprintf(buffer, sizeof(buffer), "test loop...\n");
    print_line(buffer);

    wait(1000);
    testLoop(rotaryActivity, hueActivity);
}

// void testRotaryGradient()
// {
//     char buffer[32];
//     uint16_t tRows = 4;
//     uint16_t tColumns = 9;
//     Range range(0, tRows * tColumns);
//     Grid grid(range(), tColumns, GRID_ROWS);

//     GradientPalette palette(VARY_HUE);
//     palette.HSL(hue_red, saturation_size, luminance_size / 8);
//     palette(hue_green, hue_blue + hue_limit);
//     palette.Gamma(true);
//     palette.Fit(grid);

//     GradientUpdater gradientUpdater(grid, palette, 20);
//     Activity gradientActivity(&gradientUpdater);
//     palette(hue_red, hue_blue);
//     auto pw = gradientUpdater.Update();
//     TEST_ASSERT_EQUAL(pw, 20);
//     snprintf(buffer, sizeof(buffer), "gradientUpdater...\n");
//     print_line(buffer);
//     wait(4000);

//     RotaryUpdater rotary(encoderA, encoderB, button, true);
//     snprintf(buffer, sizeof(buffer), "test loop...\n");
//     print_line(buffer);

//     wait(2000);
//     testLoop(rotary, gradientActivity);
// }

#endif

void testPixelActivities()
{
#ifdef ARDUINO
    RUN_TEST(testRotaryLuminance);
    // RUN_TEST(testRotaryGradient);
#endif
    // RUN_TEST(testHueGradientActivity);
}
