// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "Benchmark.h"

#include "Monitor.h"
#include "Controller.h"
// #include "GradientActivity.h"
// #include "Grid.h"

extern pixel::Controller &Pixels;

// pixel::Controller &Pixels = pixelController;

void testBenchMark();
void testPixelDevices();
void testPixelControllers();
void testMatrixMappers();
void testPalettes();

// void testColorFilter();
void testPixelGrids();
void testBuildControllers();
void testPixelActivities();

using glow::Monitor;
using glow::print_line;

void run()
{
    UNITY_BEGIN();
    testBuildControllers();
    // testBenchMark();
    // testPixelDevices();
    // testPixelControllers();
    // testMatrixMappers();
    // testPalettes();
    // testPixelGrids();
    testPixelActivities();
    UNITY_END();
}

#include "Activities.h"

#ifdef ARDUINO

void setup()
{
    // BuildController();
    Serial.begin(115200);
    delay(2000);
    glow::Benchmark::Setup();

    run();

    paletteA.Gamma(true);
    activityA.State(2);
    activityA.PulseWidth(100);
    sliderA.PulseWidth(100);

    paletteB.Gamma(true);
    activityB.State(0);
    activityB.PulseWidth(500);
}

void loop()
{
    Monitor::Cycle();
    activityA.Pulse();
    activityB.Pulse();
    // sliderA.Pulse();
}

#else
int main(int argc, char **argv)
{
    glow::Benchmark::Setup();
    run();
}
#endif // ARDUINO
