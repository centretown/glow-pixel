// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "base.h"
#include "BlinkActivity.h"
#include "PixelController.h"
#include "config.h"

using namespace glow;

void testPixelDevices();
void testPixelControllers();
void testPixelColor();
void testColorFilter();
void testPixelMapper();
void testPixelStrip();

// void testStripActivities();

PinDevice blinkPin;
BlinkSettings blink(&blinkPin);
BlinkMonitor monitor(&blink);
BlinkActivity blinker(&monitor, &blink);

void run()
{
    UNITY_BEGIN();
    testPixelDevices();
    testPixelControllers();
    // testPixelColor();
    // testColorFilter();
    testPixelMapper();
    // testPixelStrip();
    // testStripActivities();
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
    blink.On(150);
    blink.Off(350);
}

void loop()
{
    Monitor::Cycle();
    blinker.Pulse();
}

#else
int main(int argc, char **argv)
{
    run();
}
#endif // ARDUINO