// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED

// #include <unity.h>
// #include "base.h"
// #include "config.h"
// #include "Activity.h"
// #include "PixelController.h"
// #include "PixelStrip.h"
// #include "SolidActivity.h"
// #include "TimeMonitor.h"

// using namespace glow;


// PixelController pixelController(pixelWriters, pixelWritersCount);
// uint16_t testActivity(Activity *activity, uint16_t max_ticks, uint64_t max_millis)
// {
//     uint16_t ticks = 0;
//     Activity::Cycle();

//     while (!activity->Dead() && ticks <= max_ticks)
//     {
//         Activity::Cycle();

//         if (activity->Pulse())
//         {
//             ticks++;
//         }

//         auto now = Activity::Now();
//         if (max_millis < now)
//         {
//             break;
//         }
//     }

//     return ticks;
// }

// void testPixelSolid()
// {
//     Activity::Cycle();
//     PixelStrip settings;
//     settings.Color().Red(0xff);
//     SolidActivity solid(settings);
//     solid.Setup();

//     uint16_t max_ticks = 0;
//     uint64_t max_millis = Activity::Now() + 2000;
//     uint16_t ticks = testActivity(&solid, max_ticks, max_millis);
//     Activity::Cycle();
//     solid.Reset();

//     Activity::Cycle();
//     TEST_ASSERT_LESS_OR_EQUAL(max_millis + 10, Activity::Now());
//     TEST_ASSERT_EQUAL(max_ticks, ticks);

//     TimeMonitor timer(Activity::Now() + 2000, Activity::Now() + 1000);
//     settings.Color().RGB(0, 0, 0xff);
//     solid.Setup();
//     max_millis = timer.End() + 1000;
//     ticks = testActivity(&solid, max_ticks, max_millis);
// }

// void testStripActivities()
// {
//     PixelStrip::Setup(&pixelController);
//     RUN_TEST(testPixelSolid);

//     // TimeMonitor monitor;
// }