// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "Benchmark.h"

#include "BlinkActivity.h"
#include "Controller.h"

extern pixel::Controller &Pixels;

// pixel::Controller &Pixels = pixelController;

void testBenchMark();
void testPixelDevices();
void testPixelControllers();
void testMatrixMappers();
void testPalettes();


// void testColorFilter();
// void testPixelGrids();

void testBuildControllers();

glow::PinDevice blinkPin;
glow::BlinkSettings blink(&blinkPin);
glow::BlinkMonitor monitor(&blink);
glow::BlinkActivity blinker(&monitor, &blink);

void run()
{
    UNITY_BEGIN();
    testBuildControllers();
    testBenchMark();
    testPixelDevices();
    testPixelControllers();
    testMatrixMappers();
    testPalettes();

    // testColorFilter();
    // testPixelGrids();
    UNITY_END();
}

#ifdef ARDUINO

void setup()
{
    // BuildController();
#ifdef ARDUINO
    Serial.begin(115200);
#endif
    delay(2000);
    glow::Benchmark::Setup();
    run();
    blinkPin.Setup();
    blinker.Reset();
    blink.On(50);
    blink.Off(400);
}

void loop()
{
    glow::Monitor::Cycle();
    blinker.Pulse();
}

#else
int main(int argc, char **argv)
{
    glow::Benchmark::Setup();
    run();
}
#endif // ARDUINO
