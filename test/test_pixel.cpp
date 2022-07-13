// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "base.h"
#include "BlinkActivity.h"
#include "Controller.h"
#include "config.h"

using namespace pixel;

void testPixelDevices();
void testPixelControllers();
void testPixelColor();
void testColorFilter();
void testPixelMapper();
void testPixelStrip();
void testPixelGrids();
void testColorPalettes();
void testPixelColorHsv();
void testGradientPalettes();
void testPixelIndeces();
void testPixelSpinner();

// void testStripActivities();

glow::PinDevice blinkPin;
glow::BlinkSettings blink(&blinkPin);
glow::BlinkMonitor monitor(&blink);
glow::BlinkActivity blinker(&monitor, &blink);

void run()
{
    UNITY_BEGIN();
    testPixelDevices();
    testPixelIndeces();
    testPixelControllers();
    testPixelColor();
    testColorFilter();
    testPixelMapper();
    testPixelSpinner();
    testPixelGrids();
    testColorPalettes();
    testPixelColorHsv();
    testGradientPalettes();
    testPixelSpinner();
    UNITY_END();
}

#ifdef ARDUINO

void setup()
{
    delay(2000);
    Pixels.Setup();
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
    run();
}
#endif // ARDUINO
