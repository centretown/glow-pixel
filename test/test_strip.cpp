// Copyright (c) 2022 Dave Marsh. See LICENSE.

#define UNITY_INCLUDE_PRINT_FORMATTED
#include <unity.h>
#include "base.h"
#include "StripActivities.h"

void testPixelWriters();    

StripSettings stripSettings;
StripActivities strip(stripSettings);

void run()
{
    UNITY_BEGIN();
    testPixelWriters();
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
    now = millis();
    strip.Pulse(now);
}

#else
int main(int argc, char **argv)
{
    run();
}
#endif // ARDUINO
