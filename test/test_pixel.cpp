// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "Benchmark.h"

#include "Monitor.h"
#include "Controller.h"

extern pixel::Controller &Pixels;

void testBenchMark();
void testPixelDevices();
void testPixelControllers();
void testMatrixMappers();
void testPalettes();

// void testColorFilter();
void testPixelGrids();
void testBuildControllers();
void testPixelActivities();

using color::hue_red;
using color::hue_yellow;
using glow::Monitor;
using glow::print_line;

void run()
{
    UNITY_BEGIN();
    testBuildControllers();
    testBenchMark();
    testPixelDevices();
    // testPixelControllers();
    // testMatrixMappers();
    // testPalettes();
    // testPixelGrids();
    testPixelActivities();
    UNITY_END();
}

#include "Activities.h"

#ifdef ARDUINO

#include "RotaryUpdater.h"
#include "StateHandler.h"

using glow::StateHandler;
using glowui::RotaryUpdater;

const uint8_t encoderA = 21;
const uint8_t encoderB = 5;
const uint8_t button = 15;

RotaryUpdater rotary(encoderA, encoderB, button, true);
Activity rotaryActivity(&rotary, &updaterA);
Activity rotaryActivityB(&rotary, &updaterB);

void setup()
{
    Serial.begin(115200);
    delay(2000);
    glow::Benchmark::Setup();

    run();

    paletteA.HSL(hue_red, saturation_size, 7);
    paletteA.Gamma(true);
    activityA.PulseWidth(100);
    paletteA(hue_red, hue_yellow + 128);
    paletteA.Fit(gridA);

    rotaryActivity.PulseWidth(2);
    rotaryActivityB.PulseWidth(2);
    rotary.Bounds(0, 255);
    // sliderA.PulseWidth(100);

    paletteB.HSL(hue_red, saturation_size, 7);
    paletteB.Gamma(true);
    paletteB(hue_red, hue_yellow);
    paletteB.Fit(gridB);
    activityB.PulseWidth(500);
}

void loop()
{
    Monitor::Cycle();
    rotaryActivity.Pulse();
    rotaryActivityB.Pulse();
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
