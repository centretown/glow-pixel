// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "base.h"
#include "StripActivities.h"

void testPixelWriters();
void testStripActivities();
void testPixelGroups();

StripSettings stripSettings;
StripActivities strip(stripSettings);

void run()
{
    UNITY_BEGIN();
    testPixelWriters();
    testPixelGroups();
    testStripActivities();
    UNITY_END();
}

#ifdef ARDUINO

void setup()
{
    delay(2000);
    run();
    strip.Setup();
}

uint64_t now;
void loop()
{
    Activity::Cycle();
    strip.Pulse();
}

#else
int main(int argc, char **argv)
{
    run();
}
#endif // ARDUINO
